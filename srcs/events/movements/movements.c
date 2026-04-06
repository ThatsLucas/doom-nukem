/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:21:43 by edurance          #+#    #+#             */
/*   Updated: 2026/04/06 15:01:49 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"

/*Gere les mouvements mediaux*/
static void	medial_moves(t_ply *ply, t_game *game)
{
	float	steps;
	float	next_x;
	float	next_y;
	int		direction;
	(void)game;

	if (ply->keys.w && ply->keys.s)
		return ;
	steps = 10.0f;
	if (ply->keys.w)
		direction = 1;
	if (ply->keys.s)
		direction = -1;
	next_x = ply->pos_x + ply->dir_x * steps * direction;
	next_y = ply->pos_y + ply->dir_y * steps * direction;
	ply->pos_x = next_x;
	ply->pos_y = next_y;
}

/*Gere les mouvements lateraux*/
static void	lateral_moves(t_ply *ply, t_game *game)
{
	float	steps;
	float	next_x;
	float	next_y;
	float	ax;
	float	ay;
	(void)game;

	if (ply->keys.a && ply->keys.d)
		return ;
	steps = 10.0f;
	ax = ply->dir_x * cosf((M_PI / 2) * -1) - ply->dir_y * sinf((M_PI / 2) * -1);
	ay = ply->dir_x * sinf((M_PI / 2) * -1) + ply->dir_y * cosf((M_PI / 2) * -1);
	if (ply->keys.a)
	{
		next_x = ply->pos_x + ax * steps;
		next_y = ply->pos_y + ay * steps;
	}
	if (ply->keys.d)
	{
		next_x = ply->pos_x - ax * steps;
		next_y = ply->pos_y - ay * steps;
	}
	ply->pos_x = next_x;
	ply->pos_y = next_y;
}

/*Gere les mouvements du joueur*/
void	ply_movements(t_ply *ply, t_game *game)
{
	if (ply->keys.w || ply->keys.s)
		medial_moves(ply, game);
	if (ply->keys.a || ply->keys.d)
		lateral_moves(ply, game);
}
