/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:12:27 by edurance          #+#    #+#             */
/*   Updated: 2026/04/19 11:48:13 by edurance         ###   ########.fr       */
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
		if (item->picked_up)
			continue;
		pickup_item(game, item);
	}
}
