/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickup_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:48:38 by edurance          #+#    #+#             */
/*   Updated: 2026/04/10 10:57:02 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventory/Inventory.h"
#include "Player.h"
#include "Game.h"

/* Pickup a consumable -> Battery, heal or fuel */
static void	pickup_consumable(t_game *game, t_ground_item *item)
{
	t_ply	*ply = game->ply;
	t_consumable *cons = &item->data.cons;
	
	if (cons->amount == 0)
		return ;

	switch (cons->type)
	{
		case CONS_HEAL:
			ply->hp += cons->amount;
			if (ply->hp > MAX_HP)
				ply->hp = MAX_HP;
			break;
		case CONS_FUEL:
			for (int i = 0; i < ply->inventory.tool_count; i++)
			{
				if (ply->inventory.tools[i].type == TOOL_JETPACK)
				{
					ply->inventory.tools[i].data.fuel += cons->amount;
					if (ply->inventory.tools[i].data.fuel > MAX_FUEL)
						ply->inventory.tools[i].data.fuel = MAX_FUEL;
					break;
				}
			}
			break;
		case CONS_BATTERY:
			for (int i = 0; i < ply->inventory.tool_count; i++)
			{
				if (ply->inventory.tools[i].type == TOOL_FLASHLIGHT)
				{
					ply->inventory.tools[i].data.battery += cons->amount;
					if (ply->inventory.tools[i].data.battery > MAX_BATTERY)
						ply->inventory.tools[i].data.battery = MAX_BATTERY;
					break;
				}
			}
			break;
		default:
			break;
	}
}

/* Adds ammo or a weapon in your inventory */
static void	pickup_weapon(t_game *game, t_ground_item *item)
{
	t_ply		*ply = game->ply;
	t_weapon	*weap = &item->data.weap;

	for (int i = 0; i < ply->inventory.weap_count; i++)
	{
		if (ply->inventory.weapons[i].type == weap->type)
		{
			ply->inventory.weapons[i].ammo += weap->ammo;
			if (ply->inventory.weapons[i].ammo > MAX_AMMO)
				ply->inventory.weapons[i].ammo = MAX_AMMO;
			return ;
		}
	}

	if (ply->inventory.weap_count < MAX_WEAPONS)
	{
		ply->inventory.weapons[ply->inventory.weap_count] = *weap;
		ply->inventory.weap_count += 1;
	}
}

static void	pickup_tool(t_game *game, t_ground_item *item)
{
	t_ply	*ply = game->ply;
	t_tool	*tool = &item->data.tool;

	for (int i = 0; i < ply->inventory.tool_count; i++)
	{
		if (ply->inventory.tools[i].type == tool->type)
		{
			return ;
		}
	}
	
	if (ply->inventory.tool_count < MAX_TOOLS)
	{
		ply->inventory.tools[ply->inventory.tool_count] = *tool;
		ply->inventory.tool_count += 1;
	}
}

/* Choses pickup consumable/weapon depending on the item type if you are near the item */
void	pickup_item(t_game *game, t_ground_item *item)
{
	t_ply	*ply = game->ply;
	if (!item)
		return ;
	if (!is_near(ply->pos_x, ply->pos_y, item->pos_x, item->pos_y, item->pickup_range))
		return ;

	if (item->type == ITEM_CONSUMABLE)
		pickup_consumable(game, item);
	else if (item->type == ITEM_WEAPON)
		pickup_weapon(game, item);
	else if (item->type == ITEM_TOOL)
		pickup_tool(game, item);

	game->flash_alpha = 0.5f;
	item->pos_x = -1000;
}
