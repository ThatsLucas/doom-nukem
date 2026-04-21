/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:45:14 by edurance          #+#    #+#             */
/*   Updated: 2026/04/21 12:54:34 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "inventory/Items.h"

/* Adds an item to the list and realloc it if needed */
void	add_item(t_game *game, t_ground_item new_item)
{
	t_ground_item *tmp;

	if (game->items_count >= game->items_capacity)
	{
		game->items_capacity += 16;
		tmp = realloc(game->items, game->items_capacity * sizeof(t_ground_item));
		if (!tmp)
			exit_game(game, "failed reaaloc on items");
		game->items = tmp;
	}
	game->items[game->items_count++] = new_item;
}
