/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:12:27 by edurance          #+#    #+#             */
/*   Updated: 2026/04/09 12:09:55 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventory/Items.h"
#include "Game.h"

/* Checks all the items in the game loop */
void	update_item(t_game *game)
{
	for (int i = 0; i < game->items_count; i++)
	{
		t_ground_item *item = &game->items[i];
		if (item->pos_x < 0)
			continue;

		pickup_item(game, item);
	}
}
