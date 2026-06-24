/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:42:28 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/23 17:16:39 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

float	to_pixelX(float x, t_game *game)
{
	static float	coeff = 0.0f;

	if (!coeff)
		coeff = game->screenSize[0] / game->map->mapSize.x;

	return (x * coeff);
}

float	to_pixelY(float y, t_game *game)
{
	static float	coeff = 0.0f;

	if (!coeff)
	coeff = game->screenSize[1] / game->map->mapSize.y;

	return (y * coeff);
}
