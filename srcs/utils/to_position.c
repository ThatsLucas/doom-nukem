/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:22:20 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/23 17:16:46 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

float	to_PosX(float x, t_game *game)
{
	static float	coeff = 0.0f;

	if (!coeff)
		coeff = game->screenSize[0] / game->map->mapSize.x;

	return (x / coeff);
}

float	to_PosY(float y, t_game *game)
{
	static float	coeff = 0.0f;

	if (!coeff)
	coeff = game->screenSize[1] / game->map->mapSize.y;

	return (y / coeff);
}
