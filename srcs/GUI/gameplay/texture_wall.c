/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:41:37 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/11 11:44:40 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Raycasting/Types.h"
#include "GUI.h"

void	texture_wall(t_game *game, t_ray *ray)
{
	t_RGB		c;
	float		text_y_start;
	int			tex_x, tex_y;
	SDL_Surface	*surface = game->surface[ray->splitter.textureID];
	int			draw_start_orig = (game->screenSize[1] / 2) - (ray->height / 2);
	int			draw_end_orig   = (game->screenSize[1] / 2) + (ray->height / 2);

	ray->draw_start	= draw_start_orig > 0 ? draw_start_orig : 0;
	ray->draw_end	= draw_end_orig > game->screenSize[1] ? game->screenSize[1] : draw_end_orig;

	text_y_start	= (float)(ray->draw_start - draw_start_orig) / (float)ray->height;
	ray->wall_x		= dist_vect(ray->splitter.start, ray->intersection) / dist_vect(ray->splitter.start, ray->splitter.end);

	for (int i = ray->draw_start; i < ray->draw_end; ++i)
	{
		ray->text_y = text_y_start + (float)(i - ray->draw_start) / (float)ray->height;
		tex_x		= (int)(ray->wall_x * surface->w);
		tex_y		= (int)(ray->text_y * surface->h);
		c			= game->text_colors[ray->splitter.textureID][tex_y * surface->w + tex_x];

		game->frame_buffer[i * game->screenSize[0] + ray->screen_x] = 
					(c.r << 16) | (c.g << 8) | c.b;
	}

	return ;
}
