/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:21:43 by edurance          #+#    #+#             */
/*   Updated: 2026/04/05 17:22:03 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"

/*Gere les mouvements mediaux*/
static void	medial_moves(int key, t_ply *ply, t_game *game)
{
	float	steps;
	float	next_x;
	float	next_y;
	int		direction;
	(void)game;

	steps = 10.0f;
	if (key == 119)
		direction = 1;
	if (key == 115)
		direction = -1;
	next_x = ply->pos_x + ply->dir_x * steps * direction;
	next_y = ply->pos_y + ply->dir_y * steps * direction;
	ply->pos_x = next_x;
	ply->pos_y = next_y;
}

/*Gere les mouvements lateraux*/
static void	lateral_moves(int key, t_ply *pl, t_game *game)
{
	float	steps;
	float	next_x;
	float	next_y;
	float	ax;
	float	ay;
	(void)game;

	steps = 10.0f;
	ax = pl->dir_x * cosf((M_PI / 2) * -1) - pl->dir_y * sinf((M_PI / 2) * -1);
	ay = pl->dir_x * sinf((M_PI / 2) * -1) + pl->dir_y * cosf((M_PI / 2) * -1);
	if (key == 97)
	{
		next_x = pl->pos_x + ax * steps;
		next_y = pl->pos_y + ay * steps;
	}
	else
	{
		next_x = pl->pos_x - ax * steps;
		next_y = pl->pos_y - ay * steps;
	}
	pl->pos_x = next_x;
	pl->pos_y = next_y;
}

/*Gere les mouvements du joueur*/
void	ply_movements(int key, t_ply *ply, t_game *game)
{
	if (key == 119 || key == 115)
		medial_moves(key, ply, game);
	else if (key == 97 || key == 100)
		lateral_moves(key, ply, game);
}
