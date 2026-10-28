/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:41:28 by edurance          #+#    #+#             */
/*   Updated: 2026/10/20 16:28:35 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"
#include "GUI/GUI.h"
#include <math.h>
#include <stdlib.h>

/* Données de caméra communes à toutes les entités d’une image. */
typedef struct s_sprite_ctx
{
	int		sw;
	float	half_sw;
	float	half_sh;
	float	focal;
	float	inv_det;
	float	closest;
	t_vect2	plane;
	t_vect2	dir;
	t_vect2	pos;
	float	z;
	float	pitch;
}	t_sprite_ctx;

/* Taille d’une entité dans le monde (hauteur, ratio, z de base). */
typedef struct s_sprite_dim
{
	float	h;
	float	aspect;
	float	z;
}	t_sprite_dim;

/* Initialise le contexte de rendu du sprite. */
static void	init_sprite_ctx(t_game *game, t_sprite_ctx *c)
{
	float	camera_scale = tanf(game->settings.FOV * 0.5f);

	c->sw = game->screenSize[0];
	c->half_sw = c->sw * 0.5f;
	c->half_sh = game->screenSize[1] * 0.5f;
	c->focal = c->half_sw / camera_scale;
	c->plane = get_cam_plane(camera_scale, game->ply->dir);
	c->dir = game->ply->dir;
	c->pos = game->ply->pos;
	c->z = game->ply->z;
	c->pitch = game->ply->pitch;
	c->inv_det = 1.0f / (c->plane.x * c->dir.y - c->dir.x * c->plane.y);
	c->closest = FLT_MAX;
}

/* Sélectionne la texture correspondant à l’entité. */
static t_tex	*select_entity_texture(t_entity *e, t_vect2 ply_pos)
{
	long long	current = get_time_ms();
	int			is_shooting = e->last_shot_time > 0 && (current - e->last_shot_time) < (e->fire_rate * 0.7);

	if (e->status == E_STATUS_DEAD)
		return (e->texture_dead);
	if (is_shooting && e->texture_shoot && (e->type == ENTITY_ENEMY || e->type == ENTITY_BOSS))
		return (e->texture_shoot);
	if (e->textures && e->num_frames > 0)
		return (e->textures[get_directional_frame(e, ply_pos.x, ply_pos.y)]);
	return (e->texture);
}

/* Calcule la taille d’affichage d’une entité vivante. */
static void	compute_alive_size(t_entity *e, t_sprite_dim *d)
{
	if (e->sprite_h > 0.0f)
		d->h = (e->sprite_h / 600.0f) * 1.8f;
	else if (e->type == ENTITY_ENEMY || e->type == ENTITY_PNJ)
	{
		d->h = 1.8f;
		d->z = e->z - 0.05f;
	}
	else
		d->h = 0.5f;

	if (e->sprite_w > 0.0f && e->sprite_h > 0.0f)
		d->aspect = e->sprite_w / e->sprite_h;
	else if (e->type == ENTITY_ENEMY || e->type == ENTITY_PNJ)
		d->aspect = 0.6f;
	else
		d->aspect = 1.0f;
}

/* Calcule la taille d’affichage de l’entité. */
static t_sprite_dim	compute_entity_size(t_entity *e)
{
	t_sprite_dim	d;

	d.z = e->z;
	if (e->type == ENTITY_BOSS)
		d.z = e->z - 0.35f;
	if (e->status == E_STATUS_DEAD && e->type == ENTITY_ENEMY)
	{
		d.h = 1.0f;
		d.aspect = 0.95f;
		d.z = e->z - 0.40f;
	}
	else if (e->status == E_STATUS_DEAD && e->type == ENTITY_BOSS)
	{
		d.h = 1.0f;
		d.aspect = 3.0f;
		d.z = e->z;
	}
	else
		compute_alive_size(e, &d);
	return (d);
}

/* Projette l’entité à l’écran, renvoie 0 si elle est invisible. */
static int	project_entity(t_sprite_ctx *c, t_entity *e, SDL_Rect *dest, float *depth)
{
	float			dx = e->x - c->pos.x;
	float			dy = e->y - c->pos.y;
	float			transform_x;
	float			transform_y;
	t_sprite_dim	d;

	if (dx * dx + dy * dy > MAX_ENTITY_DIST_RENDER_SQ)
		return (0);
	transform_x = c->inv_det * (c->dir.y * dx - c->dir.x * dy);
	transform_y = c->inv_det * (-c->plane.y * dx + c->plane.x * dy);
	if (transform_y <= 0.1f)
		return (0);
	d = compute_entity_size(e);

	float	inv_ty = 1.0f / transform_y;
	int		sx = (int)(c->half_sw + c->half_sw * transform_x * inv_ty);
	float	dz_bot = d.z - c->z;
	float	dz_top = d.z + d.h - c->z;
	int		y_bot = (int)(c->half_sh - dz_bot * c->focal * inv_ty + c->pitch);
	int		y_top = (int)(c->half_sh - dz_top * c->focal * inv_ty + c->pitch);
	int		sprite_h = y_bot - y_top;
	int		sprite_w = (int)(sprite_h * d.aspect);

	if (sprite_h <= 0 || sprite_w <= 0)
		return (0);
	if (sx + sprite_w / 2 < 0 || sx - sprite_w / 2 >= c->sw)
		return (0);
	*dest = (SDL_Rect){.x = sx - sprite_w / 2, .y = y_top, .w = sprite_w, .h = sprite_h};
	*depth = transform_y;
	return (1);
}

/* Met à jour la cible du viseur visible. */
static void	update_crosshair_target(t_game *game, t_sprite_ctx *c, t_entity *e, SDL_Rect dest, float depth)
{
	int	cx = (int)c->half_sw;
	int	cy = (int)c->half_sh;

	if (cx >= dest.x && cx <= dest.x + dest.w && cy >= dest.y && cy <= dest.y + dest.h
		&& depth < c->closest && depth < game->z_buffer[cy * c->sw + cx])
	{
		c->closest = depth;
		game->ply->crosshair_target = e;
	}
}

/* Met à jour et affiche les entités. */
void	render_entities(t_game *game)
{
	t_sprite_ctx	c;
	t_entity		*e;
	t_tex			*tex;
	SDL_Rect		dest;
	float			depth;

	init_sprite_ctx(game, &c);
	update_entities(game, &game->entities);
	game->ply->crosshair_target = NULL;
	for (int i = 0; i < game->entities.count; i++)
	{
		e = &game->entities.list[i];
		if (e->sector < 0 || e->sector >= game->map->num_sectors
			|| !isfinite(e->x) || !isfinite(e->y))
			continue ;
		e->z = get_plane_z(game->map->sectors[e->sector].floor_plane, e->x, e->y);
		tex = select_entity_texture(e, c.pos);
		if (!project_entity(&c, e, &dest, &depth))
			continue ;
		update_crosshair_target(game, &c, e, dest, depth);
		if (tex)
			draw_sprite_zbuf(game, tex, dest, depth, game->map->sectors[e->sector].light_level);
	}
}
