/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_ceiling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:44:59 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/11 12:51:58 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Raycasting/Types.h"
#include "GUI.h"

static void	increment_ceiling(t_vect2 *ceiling, t_vect2 step)
{
	(*ceiling).x	+= step.x;
	(*ceiling).y	+= step.y;

	return ;
}

void	texture_ceiling(t_game *game, t_ray *rays)
{
	t_RGB		c;
	float		rowDistance;
	int			tex_x, tex_y;
	t_vect2		ceilingStep, ceiling;
	t_vect2		ray_dir_left	= rays[0].ray_dir;
	t_vect2		ray_dir_right	= rays[game->screenSize[0] - 1].ray_dir;
	SDL_Surface	*surface		= game->surface[3];

	for (int y = 0; y < game->screenSize[1] / 2; ++y)
	{
		rowDistance			= (float)(game->screenSize[1] / 2) / (float)(game->screenSize[1] / 2 - y);
		ceilingStep.x		= rowDistance * (ray_dir_right.x - ray_dir_left.x) / game->screenSize[0];
		ceilingStep.y		= rowDistance * (ray_dir_right.y - ray_dir_left.y) / game->screenSize[0];
		ceiling.x			= game->ply->pos.x + rowDistance * ray_dir_left.x;
		ceiling.y			= game->ply->pos.y + rowDistance * ray_dir_left.y;
		for (int x = 0; x < game->screenSize[0]; ++x)
		{
			if (y >= rays[x].draw_start)
			{
				increment_ceiling(&ceiling, ceilingStep);
				continue ;
			}
			tex_x			= ((int)(ceiling.x * surface->w) % surface->w + surface->w) % surface->w;
			tex_y			= ((int)(ceiling.y * surface->h) % surface->h + surface->h) % surface->h;

			c				= game->text_colors[3][tex_y * surface->w + tex_x];
			game->frame_buffer[y * game->screenSize[0] + x] = (c.r << 16) | (c.g << 8) | c.b;

			increment_ceiling(&ceiling, ceilingStep);
		}
	}

	return ;
}
