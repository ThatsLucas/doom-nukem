/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:22:20 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/09 11:23:52 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

float	to_PosX(float x, t_game *game)
{
	static float	coeff = 0.0f;

	if (!coeff)
		coeff = game->screenSize[0] / game->mapSize[0];

	return (x / coeff);
}

float	to_PosY(float y, t_game *game)
{
	static float	coeff = 0.0f;

	if (!coeff)
	coeff = game->screenSize[1] / game->mapSize[1];

	return (y / coeff);
}
