/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 12:30:00 by edurance          #+#    #+#             */
/*   Updated: 2026/08/11 14:20:44 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "inventory/Items.h"

/* Libère tous les objets au sol. */
void cleanup_items(t_game *game)
{
	if (!game || !game->items)
		return;

	for (int i = 0; i < game->items_count; i++)
	{
		t_ground_item *item = &game->items[i];
		if (item->texture)
		{
			free(item->texture->colors);
			free(item->texture);
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
