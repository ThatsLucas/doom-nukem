/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:04:59 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/15 13:16:26 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI.h"

/* Affiche le ciel si il y en a un */
static void	draw_sky(t_game *game, t_ray *ray, int x, t_sector *sector)
{
	int		sW		= game->screenSize[0], sH = game->screenSize[1];
	int		start	= SDL_clamp(ray->y_top, 0, sH - 1);
	int		end		= SDL_clamp(ray->y_wall_top, 0, ray->y_bot);
	int		tex_x, tex_y;
	t_RGB	c;

	float angle = atan2(ray->dir.y, ray->dir.x) + M_PI;
	tex_x = (int)(angle / (2 * M_PI) * game->map->surface[sector->sky_tex]->w) % game->map->surface[sector->sky_tex]->w;
	for (int y = start; y < end; y++)
	{
		tex_y = (int)((float)y / (sH / 2 + game->ply->pitch) * game->map->surface[sector->sky_tex]->h) % game->map->surface[sector->sky_tex]->h;
		if (tex_x < 0) tex_x += game->map->surface[sector->sky_tex]->w;
		if (tex_y < 0) tex_y += game->map->surface[sector->sky_tex]->h;

		c = game->map->text_colors[sector->sky_tex][tex_y * game->map->surface[sector->sky_tex]->w + tex_x];
		game->frame_buffer[y * sW + x] = write_color(c.r, c.g, c.b, sector->light_level);
	}
	if (ray->y_wall_top > ray->y_top)
		ray->y_top = ray->y_wall_top;

	return ;
}

/* affiche un plafond */
void	draw_ceil(t_game *game, t_ray *ray, int x, t_sector *sector)
{
	int			sW		= game->screenSize[0], sH = game->screenSize[1];
	int			start	= SDL_clamp(ray->y_top, 0, sH - 1);
	int			end		= SDL_clamp(ray->y_wall_top, 0, ray->y_bot);
	int			tex_x, tex_y;
	t_RGB		c;
	SDL_Surface	*S		= game->map->surface[sector->ceil_tex];

	if (sector->sky_tex >= 0)
	{
		draw_sky(game, ray, x, sector);
		return ;
	}
	float	dot		= ray->dir.x * game->ply->dir.x + ray->dir.y * game->ply->dir.y;
	float	numer	= -(sector->ceil_plane.a * game->ply->pos.x
					+ sector->ceil_plane.b * game->ply->pos.y
					+ sector->ceil_plane.c * game->ply->z
					+ sector->ceil_plane.d);
	float	denom_xy= sector->ceil_plane.a * ray->dir.x / dot
					+ sector->ceil_plane.b * ray->dir.y / dot;

	for (int y = start; y < end; y++)
	{
		float vz	= (float)(sH / 2 - y + game->ply->pitch) / ray->focal;
		float dist	= numer / (denom_xy + sector->ceil_plane.c * vz);
		float wx	= game->ply->pos.x + dist * ray->dir.x / dot;
		float wy	= game->ply->pos.y + dist * ray->dir.y / dot;

		tex_x		= (int)(wx * S->w) % S->w;
		tex_y		= (int)(wy * S->h) % S->h;
		if (tex_x < 0) tex_x += S->w;
		if (tex_y < 0) tex_y += S->h;

		c = game->map->text_colors[sector->ceil_tex][tex_y * S->w + tex_x];
		game->frame_buffer[y * sW + x] = write_color(c.r, c.g, c.b, sector->light_level);
	}
	if (ray->y_wall_top > ray->y_top)
		ray->y_top = ray->y_wall_top;

	return ;
}
