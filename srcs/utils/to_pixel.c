/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:42:28 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/22 14:28:14 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

float	to_pixelX(float x, t_game *game)
{
	static float	coeff = 0.0f;

	if (!coeff)
		coeff = game->window->w / game->mapSize[0];

	return (x * coeff);
}

float	to_pixelY(float y, t_game *game)
{
	static float	coeff = 0.0f;

	if (!coeff)
	coeff = game->window->h / game->mapSize[1];

	return (y * coeff);
}
