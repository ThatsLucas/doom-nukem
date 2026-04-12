/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:05:50 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/11 12:41:59 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Raycasting/Types.h"
#include "GUI.h"

static void	increment_floor(t_vect2 *floor, t_vect2 step)
{
	(*floor).x	+= step.x;
	(*floor).y	+= step.y;

	return ;
}

void	texture_floor(t_game *game, t_ray *rays)
{
	t_RGB		c;
	float		rowDistance;
	int			tex_x, tex_y;
	t_vect2		floorStep, floor;
	t_vect2		ray_dir_left	= rays[0].ray_dir;
	t_vect2		ray_dir_right	= rays[game->screenSize[0] - 1].ray_dir;
	SDL_Surface	*surface		= game->surface[2];

	for (int y = game->screenSize[1] / 2; y < game->screenSize[1]; ++y)
	{
		rowDistance		= (float)(game->screenSize[1] / 2) / (float)(y - game->screenSize[1] / 2);
		floorStep.x		= rowDistance * (ray_dir_right.x - ray_dir_left.x) / game->screenSize[0];
		floorStep.y		= rowDistance * (ray_dir_right.y - ray_dir_left.y) / game->screenSize[0];
		floor.x			= game->ply->pos.x + rowDistance * ray_dir_left.x;
		floor.y			= game->ply->pos.y + rowDistance * ray_dir_left.y;
		for (int x = 0; x < game->screenSize[0]; ++x)
		{
			if (y >= rays[x].draw_start && y < rays[x].draw_end)
			{
				increment_floor(&floor, floorStep);
				continue ;
			}
			tex_x		= (int)(floor.x * surface->w) % surface->w;
			tex_y		= (int)(floor.y * surface->h) % surface->h;

			c			= game->text_colors[2][tex_y * surface->w + tex_x];
			game->frame_buffer[y * game->screenSize[0] + x] = (c.r << 16) | (c.g << 8) | c.b;

			increment_floor(&floor, floorStep);
		}
	}

	return ;
}
