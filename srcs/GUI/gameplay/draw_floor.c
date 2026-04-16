/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:05:56 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/16 16:43:58 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI.h"

/* affiche un sol */
void	draw_floor(t_game *game, t_ray *ray, int x, t_sector *sector)
{	
	int			sW		= game->screenSize[0], sH = game->screenSize[1];
	int			start	= SDL_clamp(ray->y_wall_bot, ray->y_top, sH - 1);
	int			end		= SDL_clamp(ray->y_bot, 0, sH - 1);
	int			tex_x, tex_y;
	t_RGB		c;
	t_tex		*tex		= &game->map->textures[sector->floor_tex];

	float dot		= ray->dir.x * game->ply->dir.x + ray->dir.y * game->ply->dir.y;
	float numer		= -(sector->floor_plane.a * game->ply->pos.x
					+ sector->floor_plane.b * game->ply->pos.y
					+ sector->floor_plane.c * game->ply->z
					+ sector->floor_plane.d);
	float	dx_dot	= ray->dir.x / dot;
	float	dy_dot	= ray->dir.y / dot;
	float	denom_xy	= sector->floor_plane.a * dx_dot
					+ sector->floor_plane.b * dy_dot;
	Uint32	*fb = &game->frame_buffer[start * sW + x];
	for (int y = start; y <= end; y++)
	{
		float vz	= (float)(sH / 2 - y + game->ply->pitch) * ray->inv_focal;
		float dist	= numer / (denom_xy + sector->floor_plane.c * vz);
		float wx	= game->ply->pos.x + dist * dx_dot;
		float wy	= game->ply->pos.y + dist * dy_dot;

		tex_x = (int)(wx * tex->w) % tex->w;
		tex_y = (int)(wy * tex->h) % tex->h;
		if (tex_x < 0) tex_x += tex->w;
		if (tex_y < 0) tex_y += tex->h;

		c	= tex->colors[tex_y * tex->w + tex_x];
		*fb	= write_color(c.r, c.g, c.b, sector->light_level);
		fb	+= sW;
	}
	if (ray->y_wall_bot < ray->y_bot)
	ray->y_bot = ray->y_wall_bot;
}
