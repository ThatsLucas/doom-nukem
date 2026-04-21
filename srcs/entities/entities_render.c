/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:41:28 by edurance          #+#    #+#             */
/*   Updated: 2026/04/21 12:54:05 by edurance         ###   ########.fr       */
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
void render_entities(t_game *game)
{
	int		sw = game->screenSize[0];
	int		sh = game->screenSize[1];
	float	half_sw = sw * 0.5f;
	float	half_sh = sh * 0.5f;
	float	focal = sw / (2.0f * FOV);
	t_vect2	plane = get_cam_plane(game->ply->dir);

	float	dir_x = game->ply->dir.x;
	float	dir_y = game->ply->dir.y;
	float	ply_x = game->ply->pos.x;
	float	ply_y = game->ply->pos.y;
	float	ply_z = game->ply->z;
	float	pitch = game->ply->pitch;
	float	inv_det = 1.0f / (plane.x * dir_y - dir_x * plane.y);

	for (int i = 0; i < game->entities.count; i++)
	{
		t_entity	*e = &game->entities.list[i];

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
		if (e->type == ENTITY_ENEMY || e->type == ENTITY_PNJ)
		{
			entity_h = 1.8f;
			aspect_ratio = 0.6f;
		}
		else
		{
			entity_h = 0.5f;
			aspect_ratio = 1.0f;
		}

		float	inv_ty = 1.0f / transform_y;
		int		sx = (int)(half_sw + focal * transform_x * inv_ty);
		float	dz_bot = e->z - ply_z;
		float	dz_top = e->z + entity_h - ply_z;
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
		if (e->texture)
			SDL_RenderCopy(game->window->renderPTR, e->texture, NULL, &dest);
	}
}
