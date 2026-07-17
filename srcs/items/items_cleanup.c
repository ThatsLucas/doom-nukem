/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 12:30:00 by edurance          #+#    #+#             */
/*   Updated: 2026/07/17 15:00:50 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "inventory/Items.h"

void cleanup_items(t_game *game)
{
	if (!game || !game->items)
		return;

	for (int i = 0; i < game->items_count; i++)
	{
		t_ground_item *item = &game->items[i];
		if (item->texture)
		{
			SDL_DestroyTexture(item->texture);
			item->texture = NULL;
		}
		if (item->texture_path)
		{
			free(item->texture_path);
			item->texture_path = NULL;
		}
	}
	free(game->items);
	game->items = NULL;
	game->items_count = 0;
	game->items_capacity = 0;
}
