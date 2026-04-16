/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:04:59 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/16 17:55:26 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI.h"

/* Affiche le ciel si il y en a un */
static void	draw_sky(t_game *game, t_ray *ray, int x, t_sector *sector)
{
	int		tex_x, tex_y;
	t_RGB	c;
	int		sW		= game->screenSize[0], sH = game->screenSize[1];
	int		start	= SDL_clamp(ray->y_top, 0, sH - 1);
	int		end		= SDL_clamp(ray->y_wall_top, 0, ray->y_bot);
	t_tex	*tex	= &game->map->textures[sector->sky_tex];

	Uint32 *fb	= &game->frame_buffer[start * sW + x];
	float angle	= atan2f(ray->dir.y, ray->dir.x) + M_PI;
	tex_x		= (int)(angle / (2 * M_PI) * tex->w) % tex->w;
	for (int y = start; y < end; y++)
	{
		tex_y = (int)((float)y / (sH / 2 + game->ply->pitch) * tex->h) % tex->h;
		if (tex_x < 0) tex_x += tex->w;
		if (tex_y < 0) tex_y += tex->h;

		c	= tex->colors[tex_y * tex->w + tex_x];
		*fb	= write_color(c.r, c.g, c.b, sector->light_level);
		fb	+= sW;
	}
	if (ray->y_wall_top > ray->y_top)
		ray->y_top = ray->y_wall_top;

	return ;
}

/* affiche un plafond */
void	draw_ceil(t_game *game, t_ray *ray, int x, t_sector *sector)
{
	int			tex_x, tex_y;
	t_RGB		c;
	int			sW		= game->screenSize[0], sH = game->screenSize[1];
	int			start	= SDL_clamp(ray->y_top, 0, sH - 1);
	int			end		= SDL_clamp(ray->y_wall_top, 0, ray->y_bot);
	t_tex		*tex	= &game->map->textures[sector->ceil_tex];

	if (sector->sky_tex >= 0)
	{
		draw_sky(game, ray, x, sector);
		return ;
	}
	float	dot		= ray->dir.x * game->ply->dir.x + ray->dir.y * game->ply->dir.y;
	float	numer	= -(sector->ceil_plane.a * game->ply->pos.x + sector->ceil_plane.b * game->ply->pos.y
					+ sector->ceil_plane.c * game->ply->z + sector->ceil_plane.d);
	float	dx_dot	= ray->dir.x / dot;
	float	dy_dot	= ray->dir.y / dot;
	float	denom_xy= sector->ceil_plane.a * dx_dot + sector->ceil_plane.b * dy_dot;

	Uint32 *fb	= &game->frame_buffer[start * sW + x];
	for (int y = start; y < end; y++)
	{
		float vz	= (float)(sH / 2 - y + game->ply->pitch) * ray->inv_focal;
		float dist	= numer / (denom_xy + sector->ceil_plane.c * vz);
		float wx	= game->ply->pos.x + dist * dx_dot;
		float wy	= game->ply->pos.y + dist * dy_dot;

		tex_x		= (int)(wx * tex->w) % tex->w;
		tex_y		= (int)(wy * tex->h) % tex->h;
		if (tex_x < 0) tex_x += tex->w;
		if (tex_y < 0) tex_y += tex->h;

		c			= tex->colors[tex_y * tex->w + tex_x];
		*fb			= write_color(c.r, c.g, c.b, sector->light_level);
		fb			+= sW;
	}
	if (ray->y_wall_top > ray->y_top)
		ray->y_top = ray->y_wall_top;
}
