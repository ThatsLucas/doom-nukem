/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:41:28 by edurance          #+#    #+#             */
/*   Updated: 2026/08/11 11:18:37 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"
#include <math.h>
#include <stdlib.h>

/*
	Fonction qui pour chaque entity va faire les calculs suivants pour le render proprement:
		- Transformation de la pos en cam (transform_y et transform_x) -> 53/54
		- Division perspective pour avoir la position sur l'ecran (inv_ty et sX)
		- Calcule la taille du sprite selon la distance et la hauteur

	A savoir qu'on skip les entities qui sont trop loin ou derriere le joueur
*/
int	get_directional_frame(t_entity *e, float px, float py)
{
	int	n = e->num_frames;

	float	to_px = e->x - px;
	float	to_py = e->y - py;

	float	e_angle = atan2f(e->dir_y, e->dir_x);
	float	view_angle = atan2f(to_py, to_px);

	float	rel = e_angle - view_angle;

	// normaliser l'angle pour qu'il soit etre PI et -PI
	while (rel > M_PI)
		rel -= 2.0f * M_PI;
	while (rel < -M_PI)
		rel += 2.0f * M_PI;

	// normaliser l'angle pour que ca donne un indexe de frame
	float	normalized = (rel + M_PI) / (2.0f * M_PI);
	int		frame = (int)(normalized * n) % n;

	if (frame < 0)
		frame += n;
	return (frame);
}

void render_entities(t_game *game)
{
	float	FOV = game->settings.FOV;
	int		sw = game->screenSize[0];
	int		sh = game->screenSize[1];
	float	half_sw = sw * 0.5f;
	float	half_sh = sh * 0.5f;
	float	camera_scale = tanf(FOV * 0.5f);
	float	focal = half_sw / camera_scale;
	t_vect2	plane = get_cam_plane(camera_scale, game->ply->dir);

	float	dir_x = game->ply->dir.x;
	float	dir_y = game->ply->dir.y;
	float	ply_x = game->ply->pos.x;
	float	ply_y = game->ply->pos.y;
	float	ply_z = game->ply->z;
	float	pitch = game->ply->pitch;
	float	inv_det = 1.0f / (plane.x * dir_y - dir_x * plane.y);
	float	closest = FLT_MAX;

	update_entities(game, &game->entities);
	game->ply->crosshair_target = NULL;
	for (int i = 0; i < game->entities.count; i++)
	{
		t_entity	*e = &game->entities.list[i];
		SDL_Texture	*tex = NULL;

		long long	current = get_time_ms();
		int			is_shooting = e->last_shot_time > 0 && (current - e->last_shot_time) < (e->fire_rate * 0.7);
		e->z = get_plane_z(game->map->sectors[e->sector].floor_plane, e->x, e->y);

		if (e->status == E_STATUS_DEAD)
			tex = e->texture_dead;
		else if (is_shooting && e->texture_shoot && (e->type == ENTITY_ENEMY || e->type == ENTITY_BOSS))
			tex = e->texture_shoot;
		else if (e->textures && e->num_frames > 0)
		{
			int frame = get_directional_frame(e, ply_x, ply_y);
			tex = e->textures[frame];
		}
		else
			tex = e->texture;

		float	dx = e->x - ply_x;
		float	dy = e->y - ply_y;

		if (dx * dx + dy * dy > MAX_ENTITY_DIST_RENDER_SQ)
			continue ;

		float	transform_x = inv_det * (dir_y * dx - dir_x * dy);
		float	transform_y = inv_det * (-plane.y * dx + plane.x * dy);
		if (transform_y <= 0.1f)
			continue ;

		float	entity_h;
		float	aspect_ratio;
		float	render_z = e->z;
		if (e->type == ENTITY_BOSS)
			render_z = e->z - 0.35f;
		if (e->status == E_STATUS_DEAD && (e->type == ENTITY_ENEMY || e->type == ENTITY_PNJ))
		{
			entity_h = 1.0f;
			aspect_ratio = 0.95f;
			render_z = e->z - 0.40f;
		}
		else
		{
			if (e->sprite_h > 0.0f)
				entity_h = (e->sprite_h / 600.0f) * 1.8f;
			else if (e->type == ENTITY_ENEMY || e->type == ENTITY_PNJ)
			{
				entity_h = 1.8f;
				render_z = e->z - 0.05f;
			}
			else
				entity_h = 0.5f;

			if (e->sprite_w > 0.0f && e->sprite_h > 0.0f)
				aspect_ratio = e->sprite_w / e->sprite_h;
			else if (e->type == ENTITY_ENEMY || e->type == ENTITY_PNJ)
				aspect_ratio = 0.6f;
			else
				aspect_ratio = 1.0f;
		}

		float	inv_ty = 1.0f / transform_y;
		int		sx = (int)(half_sw + focal * transform_x * inv_ty);
		float	dz_bot = render_z - ply_z;
		float	dz_top = render_z + entity_h - ply_z;
		int		y_bot = (int)(half_sh - dz_bot * focal * inv_ty + pitch);
		int		y_top = (int)(half_sh - dz_top * focal * inv_ty + pitch);
		int		sprite_h = y_bot - y_top;
		int		sprite_w = (int)(sprite_h * aspect_ratio);

		if (sprite_h <= 0 || sprite_w <= 0)
			continue ;

		if (sx + sprite_w / 2 < 0 || sx - sprite_w / 2 >= sw)
			continue ;

		SDL_Rect	dest = {
			.x = sx - sprite_w / 2,
			.y = y_top,
			.w = sprite_w,
			.h = sprite_h
		};

		int	cx = (int)half_sw;
		int	cy = (int)half_sh;

		if (cx >= dest.x && cx <= dest.x + dest.w && cy >= dest.y && cy <= dest.y + dest.h && transform_y < closest)
		{
			closest = transform_y;
			game->ply->crosshair_target = e;
			//printf("entity -> %d & pnj -> %d\n", game->ply->crosshair_target->type, ENTITY_PNJ);
		}

		if (tex)
			SDL_RenderCopy(game->window->renderPTR, tex, NULL, &dest);
	}
}
