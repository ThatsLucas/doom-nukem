/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:05:56 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/14 13:08:31 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI.h"

/* affiche un sol */
void	draw_floor(t_game *game, t_ray *ray, int x)
{
	int start = SDL_clamp(ray->y_wall_bot, 0, game->screenSize[1] - 1);
	int end = SDL_clamp(ray->y_bot, 0, game->screenSize[1] - 1);
	for (int y = start; y <= end; y++)
		game->frame_buffer[y * game->screenSize[0] + x] = (192 << 16) | (192 << 8) | 192;
	if (ray->y_wall_bot < ray->y_bot)
	ray->y_bot = ray->y_wall_bot;
}
