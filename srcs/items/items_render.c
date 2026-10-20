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

/* Donnees de camera communes a tous les items d'une frame */
typedef struct s_item_cam
{
	int		sw;
	float	half_sw;
	float	half_sh;
	float	focal;
	float	inv_det;
	t_vect2	plane;
	t_vect2	dir;
	t_vect2	pos;
	float	z;
	float	pitch;
}	t_item_cam;

static void	init_item_cam(t_game *game, t_item_cam *c)
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
}

/*
	Calculs pour placer un item a l'ecran :
		- Transformation de la pos en cam (transform_y et transform_x)
		- Division perspective pour avoir la position sur l'ecran (inv_ty et sX)
		- Calcule la taille du sprite selon la distance et la hauteur

	Renvoie 0 si l'item est trop loin, derriere le joueur ou hors ecran.
*/
static int	project_item(t_item_cam *c, t_ground_item *item, SDL_Rect *dest)
{
	float	dx = item->pos_x - c->pos.x;
	float	dy = item->pos_y - c->pos.y;

	// petit check pour voir si on est pas trop loin (distance d'affichage)
	if (dx * dx + dy * dy > MAX_ITEM_DIST_RENDER_SQ)
		return (0);

	float	transform_x = c->inv_det * (c->dir.y * dx - c->dir.x * dy);
	float	transform_y = c->inv_det * (-c->plane.y * dx + c->plane.x * dy);
	if (transform_y <= 0.1f)
		return (0);

	float	inv_ty = 1.0f / transform_y;
	int		sX = (int)(c->half_sw + c->focal * transform_x * inv_ty);
	float	dz_bot = item->pos_z - c->z;
	float	dz_top = dz_bot + item->world_height;
	int		y_bot = (int)(c->half_sh - dz_bot * c->focal * inv_ty + c->pitch);
	int		y_top = (int)(c->half_sh - dz_top * c->focal * inv_ty + c->pitch);
	int		sprite_h = y_bot - y_top;
	int		sprite_w = (int)(sprite_h * item->aspect_ratio);

	if (sprite_h <= 0 || sprite_w <= 0)
		return (0);
	if (sX + sprite_w / 2 < 0 || sX - sprite_w / 2 >= c->sw)
		return (0);
	*dest = (SDL_Rect){.x = sX - sprite_w / 2, .y = y_top, .w = sprite_w, .h = sprite_h};
	return (1);
}

/* On skip les items ramasses, trop loin ou derriere le joueur */
void	render_items(t_game *game)
{
	t_item_cam		c;
	t_ground_item	*item;
	SDL_Rect		dest;

	init_item_cam(game, &c);
	for (int i = 0; i < game->items_count; i++)
	{
		item = &game->items[i];
		if (item->picked_up)
			continue ;
		if (!project_item(&c, item, &dest))
			continue ;
		if (item->texture)
			SDL_RenderCopy(game->window->renderPTR, item->texture, NULL, &dest);
	}
}
