/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:40:12 by edurance          #+#    #+#             */
/*   Updated: 2026/06/09 15:37:56 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

/*
	Fonction qui pour chaque item va faire les calculs suivants pour le render proprement:
		- Transformation de la pos en cam (transform_y et transform_x) -> 53/54
		- Division perspective pour avoir la position sur l'ecran (inv_ty et sX)
		- Calcule la taille du sprite selon la distance et la hauteur

	A savoir qu'on skip les items qui sont trop loin ou derriere le joueur
*/
void	render_items(t_game *game)
{
	float	FOV = game->settings.FOV;
	int		sW = game->screenSize[0];
	int		sH = game->screenSize[1];
	float	half_sw = sW * 0.5f;
	float	half_sh = sH * 0.5f;
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

	for (int i = 0; i < game->items_count; i++)
	{
		t_ground_item	*item = &game->items[i];
		if (item->picked_up)
			continue ;

		float	dx = item->pos_x - ply_x;
		float	dy = item->pos_y - ply_y;

		// petit check pour voir si on est pas trop loin (distance d'affichage)
		if (dx * dx + dy * dy > MAX_ITEM_DIST_RENDER_SQ)
			continue ;

		float	transform_x = inv_det * (dir_y * dx - dir_x * dy);
		float	transform_y = inv_det * (-plane.y * dx + plane.x * dy);
		if (transform_y <= 0.1f)
			continue ;

		float	inv_ty = 1.0f / transform_y;
		int		sX = (int)(half_sw + focal * transform_x * inv_ty);
		float	dz_bot = item->pos_z - ply_z;
		float	dz_top = dz_bot + item->world_height;
		int		y_bot = (int)(half_sh - dz_bot * focal * inv_ty + pitch);
		int		y_top = (int)(half_sh - dz_top * focal * inv_ty + pitch);
		int		sprite_h = y_bot - y_top;
		int		sprite_w = (int)(sprite_h * item->aspect_ratio);

		if (sprite_h <= 0 || sprite_w <= 0)
			continue ;

		if (sX + sprite_w / 2 < 0 || sX - sprite_w / 2 >= sW)
			continue ;

		SDL_Rect	dest = {
			.x = sX - sprite_w / 2,
			.y = y_top,
			.w = sprite_w,
			.h = sprite_h
		};
		if (item->texture)
			SDL_RenderCopy(game->window->renderPTR, item->texture, NULL, &dest);
	}
}
