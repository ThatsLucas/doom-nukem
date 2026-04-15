/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:05:56 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/15 13:15:54 by aabouyaz         ###   ########.fr       */
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
	SDL_Surface	*S	= game->map->surface[sector->floor_tex];

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

		tex_x = (int)(wx * S->w) % S->w;
		tex_y = (int)(wy * S->h) % S->h;
		if (tex_x < 0) tex_x += S->w;
		if (tex_y < 0) tex_y += S->h;

		c = game->map->text_colors[sector->floor_tex][tex_y * S->w + tex_x];
		game->frame_buffer[y * sW + x] = write_color(c.r, c.g, c.b, sector->light_level);
	}
	if (ray->y_wall_bot < ray->y_bot)
	ray->y_bot = ray->y_wall_bot;
}
