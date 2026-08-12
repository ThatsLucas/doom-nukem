/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:05:35 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:19:46 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI/GUI.h"

/* affiche un mur */
void	draw_wall(t_game *game, t_ray *ray, int x, t_sector *sector)
{
	int		draw_top = (ray->y_wall_top > ray->y_top) ? ray->y_wall_top : ray->y_top;
	int		draw_bot = (ray->y_wall_bot < ray->y_bot) ? ray->y_wall_bot : ray->y_bot;
	t_tex	*tex;
	t_wall	*w;
	float	u_world, vh, vh_step;
	int		tex_x, tex_y;
	t_RGB	c;

	w			= &game->map->walls[ray->wall_idx];
	tex			= &game->map->textures[w->tex_mid];
	u_world		= ray->u * w->length;
	tex_x		= (int)(u_world * tex->w) % tex->w;
	vh_step = (float)tex->h / (float)(ray->y_wall_bot - ray->y_wall_top);
	vh = (float)(draw_top - ray->y_wall_top) * vh_step;
	Uint32 *fb	= &game->frame_buffer[draw_top * game->screenSize[0] + x];
	for (int y = draw_top; y < draw_bot; y++)
	{
		tex_y	= (int)vh % tex->h;
		vh		+= vh_step;
		c		= tex->colors[tex_y * tex->w + tex_x];
		*fb		= write_color(c.r, c.g, c.b, sector->light_level);
		fb		+= game->screenSize[0];
	}
}
