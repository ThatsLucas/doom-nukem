/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_create_consumables.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 12:58:20 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 12:58:20 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "inventory/Items.h"

/* heal */
void	create_item_heal(t_game *game, t_vect2 pos, int amount)
{
	t_ground_item	item;

	item.type = ITEM_CONSUMABLE;
	item.data.cons.type = CONS_HEAL;
	item.data.cons.amount = amount;
	create_ground_item(game, pos, "assets/png/items/cons/medic.png", 0.4f, item);
}

/* fuel */
void	create_item_fuel(t_game *game, t_vect2 pos, int amount)
{
	t_ground_item	item;

	item.type = ITEM_CONSUMABLE;
	item.data.cons.type = CONS_FUEL;
	item.data.cons.amount = amount;
	create_ground_item(game, pos, "assets/png/items/cons/fuel.png", 0.4f, item);
}

/* battery */
void	create_item_battery(t_game *game, t_vect2 pos, int amount)
{
	t_ground_item	item;

	item.type = ITEM_CONSUMABLE;
	item.data.cons.type = CONS_BATTERY;
	item.data.cons.amount = amount;
	create_ground_item(game, pos, "assets/png/items/cons/battery.png", 0.4f, item);
}
