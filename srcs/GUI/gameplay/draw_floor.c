/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:05:56 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/14 16:55:46 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI.h"

/* affiche un sol */
void	draw_floor(t_game *game, t_ray *ray, int x, t_sector *sector)
{
	int		sW = game->screenSize[0], sH = game->screenSize[1];
	int		start	= SDL_clamp(ray->y_wall_bot, 0, sH - 1);
	int		end		= SDL_clamp(ray->y_bot, 0, sH - 1);
	// float	dist, wx, wy;
	int		tex_x, tex_y;
	t_RGB	c;

	// dot = ray->dir.x * game->ply->dir.x + ray->dir.y * game->ply->dir.y;
	float dot		= ray->dir.x * game->ply->dir.x + ray->dir.y * game->ply->dir.y;
	float numer		= -(sector->floor_plane.a * game->ply->pos.x
					+ sector->floor_plane.b * game->ply->pos.y
					+ sector->floor_plane.c * game->ply->z
					+ sector->floor_plane.d);
	float denom_xy	= sector->floor_plane.a * ray->dir.x / dot
					+ sector->floor_plane.b * ray->dir.y / dot;
	for (int y = start; y <= end; y++)
	{
		float vz	= (float)(sH / 2 - y + game->ply->pitch) / ray->focal;
		float dist	= numer / (denom_xy + sector->floor_plane.c * vz);
		float wx	= game->ply->pos.x + dist * ray->dir.x / dot;
		float wy	= game->ply->pos.y + dist * ray->dir.y / dot;
		tex_x = (int)(wx * game->map->surface[sector->floor_tex]->w) % game->map->surface[sector->floor_tex]->w;
		tex_y = (int)(wy * game->map->surface[sector->floor_tex]->h) % game->map->surface[sector->floor_tex]->h;
		if (tex_x < 0) tex_x += game->map->surface[sector->floor_tex]->w;
		if (tex_y < 0) tex_y += game->map->surface[sector->floor_tex]->h;

		c = game->map->text_colors[sector->floor_tex][tex_y * game->map->surface[sector->floor_tex]->w + tex_x];

		game->frame_buffer[y * sW + x] = (c.r << 16) | (c.g << 8) | c.b;
	}
	if (ray->y_wall_bot < ray->y_bot)
	ray->y_bot = ray->y_wall_bot;
}
