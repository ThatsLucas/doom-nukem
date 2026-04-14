/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:05:35 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/14 13:08:40 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI.h"

/* affiche un mur */
void	draw_wall(t_game *game, t_ray *ray, int x)
{
	int	draw_top = (ray->y_wall_top > ray->y_top) ? ray->y_wall_top : ray->y_top;
	int draw_bot = (ray->y_wall_bot < ray->y_bot) ? ray->y_wall_bot : ray->y_bot;
	for (int y = draw_top; y < draw_bot; y++)
	{
		game->frame_buffer[y * game->screenSize[0] + x] = (255 << 16) | (255 << 8) | 255;
	}
}
