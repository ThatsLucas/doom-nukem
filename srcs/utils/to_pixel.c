/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:42:28 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/08 16:41:58 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

float	to_pixelX(float x, t_game *game)
{
	static float	coeff = 0.0f;

	if (!coeff)
		coeff = game->screenSize[0] / game->mapSize[0];

	return (x * coeff);
}

float	to_pixelY(float y, t_game *game)
{
	static float	coeff = 0.0f;

	if (!coeff)
	coeff = game->screenSize[1] / game->mapSize[1];

	return (y * coeff);
}
