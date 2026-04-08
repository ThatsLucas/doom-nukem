/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:48:38 by edurance          #+#    #+#             */
/*   Updated: 2026/04/08 13:20:31 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventory/Inventory.h"
#include "Player.h"
#include <math.h>

/*
	To know if the player can pickup the item

	Calculates the distance between player pos and item pos.
	If the distance is under or equal to the range* then true (1);
	Else then false (0);
*/
int	is_near(float px, float py, float ix, float iy, float range)
{
	float	dx, dy;
	float	dist_squared, range_squared;

	dx = px -ix;
	dy = py - iy;

	dist_squared = (dx * dx) + (dy * dy);
	range_squared = range * range;

	return (dist_squared <= range_squared);
}

void	pickup_consumable(t_ply *ply, t_ground_item *item)
{
	if (item->cons.amount == 0)
		return ;

	if (is_near(ply->pos_x, ply->pos_y, item->pos_x, item->pos_y, 30.0f))
	{
		if (item->cons.type == CONS_HEAL)
			ply->hp += item->cons.amount;

		item->cons.amount = 0;
		item->pos_x = -1000;
		printf("Item ramassé ! HP = %d\n", ply->hp);
	}
}
