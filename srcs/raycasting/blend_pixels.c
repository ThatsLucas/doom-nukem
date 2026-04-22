/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:37:58 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/22 14:28:14 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

/* melange les pixels pour obtenir un effet transparent */
void	blend_pixels(t_game *game, t_wall *w, t_ray *ray, int x, t_sector *sector)
{
	float	u_world, vh, vh_step;
	int		tex_x, tex_y;
	int		draw_top = (ray->y_wall_top > ray->y_top) ? ray->y_wall_top : ray->y_top;
	int		draw_bot = (ray->y_wall_bot < ray->y_bot) ? ray->y_wall_bot : ray->y_bot;
	t_tex	*tex	 = &game->map->textures[w->tex_mid];

	u_world		= ray->u * game->map->walls[ray->wall_idx].length;
	tex_x		= (int)(u_world * tex->w) % tex->w;
	t_RGB	behind;
	t_RGB	color;
	vh_step		= (float)tex->h / (float)(ray->y_wall_bot - ray->y_wall_top);
	vh = (float)(draw_top - ray->y_wall_top) * vh_step;
	Uint32 *fb	= &game->frame_buffer[draw_top * game->window->w + x];
	for (int y	= draw_top; y < draw_bot; ++y)
	{
		tex_y		= (int)vh % tex->h;
		vh			+= vh_step;
		behind.r	= (game->frame_buffer[game->window->w * y + x] >> 16) & 0xFF; // & 0xFF pour garger que les derniers 8 bits
		behind.g	= (game->frame_buffer[game->window->w * y + x] >> 8) & 0xFF;
		behind.b	= (game->frame_buffer[game->window->w * y + x]) & 0xFF;
		color		= tex->colors[tex_y * tex->w + tex_x];

		color.r		= color.r * w->alpha + behind.r * (1 - w->alpha);
		color.g		= color.g * w->alpha + behind.g * (1 - w->alpha);
		color.b		= color.b * w->alpha + behind.b * (1 - w->alpha);

		*fb			= write_color(color.r, color.g, color.b, sector->light_level);
		fb			+= game->window->w;
	}
}
