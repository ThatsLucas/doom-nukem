/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_projectile_render.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 22:37:39 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/28 22:38:43 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"
#include "GUI/GUI.h"

static t_tex	*load_proj_texture(t_game *game, char *path)
{
	t_png	png;
	t_tex	*tex;

	png.w = 0;
	png.h = 0;
	png.path = ft_strdup(path);
	if (!png.path)
		exit_game(game, "Failed to strdup projectile texture path");
	if (!process_png(&png))
		exit_game(game, "Failed to load projectile texture");
	tex = create_sprite(&png);
	if (!tex)
		exit_game(game, "Failed to create projectile sprite");
	return (tex);
}

/* Charge une seule fois les textures partagees par toutes les roquettes. */
void	load_proj_assets(t_game *game)
{
	static char		*expl_paths[3] = {
		"assets/png/hud/projectiles/explosion_1.png",
		"assets/png/hud/projectiles/explosion_2.png",
		"assets/png/hud/projectiles/explosion_3.png",
	};
	t_proj_assets	*a = &game->proj_assets;

	if (a->loaded)
		return ;
	a->fly = load_proj_texture(game, "assets/png/hud/projectiles/fireball_1.png");
	for (int i = 0; i < 3; i++)
		a->expl[i] = load_proj_texture(game, expl_paths[i]);
	a->loaded = 1;
}

/* Projette un sprite centré sur (x, y, z) a l'ecran, comme pour les entites. */
static int	project_proj(t_game *game, t_projectile *p, t_tex *tex, SDL_Rect *dest, float *depth)
{
	float	camera_scale = tanf(game->settings.FOV * 0.5f);
	float	half_sw = game->screenSize[0] * 0.5f;
	float	focal = half_sw / camera_scale;
	t_vect2	dir = game->ply->dir;
	t_vect2	plane = get_cam_plane(camera_scale, dir);
	float	inv_det = 1.0f / (plane.x * dir.y - dir.x * plane.y);
	float	dx = p->x - game->ply->pos.x;
	float	dy = p->y - game->ply->pos.y;
	float	tx = inv_det * (dir.y * dx - dir.x * dy);
	float	ty = inv_det * (-plane.y * dx + plane.x * dy);
	float	h = (p->state == PROJ_FLYING) ? 0.35f : 1.8f;

	if (ty <= 0.1f)
		return (0);
	float	inv_ty = 1.0f / ty;
	int		sx = (int)(half_sw + half_sw * tx * inv_ty);
	float	dz = p->z - game->ply->z;
	int		y_top = (int)(game->screenSize[1] * 0.5f - (dz + h * 0.5f) * focal * inv_ty + game->ply->pitch);
	int		y_bot = (int)(game->screenSize[1] * 0.5f - (dz - h * 0.5f) * focal * inv_ty + game->ply->pitch);
	int		sprite_h = y_bot - y_top;
	int		sprite_w = (int)(sprite_h * (float)tex->w / (float)tex->h);

	if (sprite_h <= 0 || sprite_w <= 0)
		return (0);
	*dest = (SDL_Rect){.x = sx - sprite_w / 2, .y = y_top, .w = sprite_w, .h = sprite_h};
	*depth = ty;
	return (1);
}

/* Affiche les roquettes et leurs explosions, cachées par les murs (z_buffer). */
void	render_projectiles(t_game *game)
{
	t_projectile	*p;
	t_tex			*tex;
	SDL_Rect		dest;
	float			depth;

	for (p = game->projectiles; p; p = p->next)
	{
		if (p->state == PROJ_FLYING && p->traveled < PROJ_HIDE_DIST)
			continue ;
		if (p->state == PROJ_FLYING)
			tex = game->proj_assets.fly;
		else
			tex = game->proj_assets.expl[SDL_min(p->expl_frame, 2)];
		if (tex && project_proj(game, p, tex, &dest, &depth))
			draw_sprite_zbuf(game, tex, dest, depth, 255); /* le feu éclaire, pas d’ombre */
	}
}

/* Supprime les roquettes actives */
void	clear_projectiles(t_game *game)
{
	t_projectile	*next;

	while (game->projectiles)
	{
		next = game->projectiles->next;
		free(game->projectiles);
		game->projectiles = next;
	}
}

void	free_projectiles(t_game *game)
{
	t_proj_assets	*a = &game->proj_assets;

	clear_projectiles(game);
	if (!a->loaded)
		return ;
	free(a->fly->colors);
	free(a->fly);
	for (int i = 0; i < 3; i++)
	{
		free(a->expl[i]->colors);
		free(a->expl[i]);
	}
	a->loaded = 0;
}
