/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:04:59 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/14 13:08:24 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI.h"

/* affiche un plafond */
void	draw_ceil(t_game *game, t_ray *ray, int x)
{
	int start = SDL_clamp(ray->y_top, 0, game->screenSize[1] - 1);
	int end = SDL_clamp(ray->y_wall_top, 0, game->screenSize[1] - 1);
	for (int y = start; y < end; y++)
		game->frame_buffer[y * game->screenSize[0] + x] = (105 << 16) | (105 << 8) | 105;
	if (ray->y_wall_top > ray->y_top)
		ray->y_top = ray->y_wall_top;
}
