/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_pickup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:48:38 by edurance          #+#    #+#             */
/*   Updated: 2026/08/11 14:20:48 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventory/Inventory.h"
#include "Player.h"
#include "Game.h"

/* Ajoute du carburant au jetpack du joueur. */
static void pickup_fuel(t_ply *ply, int amount)
{
	for (int i = 0; i < ply->inventory.tool_count; i++)
	{
		if (ply->inventory.tools[i].type == TOOL_JETPACK)
		{
			ply->inventory.tools[i].data.fuel += amount;
			if (ply->inventory.tools[i].data.fuel > MAX_FUEL)
				ply->inventory.tools[i].data.fuel = MAX_FUEL;
			break;
		}
	}
}

/* Recharge la lampe torche du joueur. */
static void pickup_battery(t_ply *ply, int amount)
{
	for (int i = 0; i < ply->inventory.tool_count; i++)
	{
		if (ply->inventory.tools[i].type == TOOL_FLASHLIGHT)
		{
			ply->inventory.tools[i].data.battery += amount;
			if (ply->inventory.tools[i].data.battery > MAX_BATTERY)
				ply->inventory.tools[i].data.battery = MAX_BATTERY;
			break;
		}
	}
}

/* Ajoute un consommable à l’inventaire du joueur. */
static void pickup_consumable(t_game *game, t_ground_item *item)
{
	t_ply *ply = game->ply;
	t_consumable *cons = &item->data.cons;

	if (cons->amount == 0)
		return;

	switch (cons->type)
	{
	case CONS_HEAL:
		ply->hp += cons->amount;
		if (ply->hp > MAX_HP)
			ply->hp = MAX_HP;
		break;
	case CONS_FUEL:
		pickup_fuel(ply, cons->amount);
		break;
	case CONS_BATTERY:
		pickup_battery(ply, cons->amount);
		break;
	default:
		break;
	}
}

/* Ajoute une arme ou des munitions à l’inventaire du joueur. */
static void pickup_weapon(t_game *game, t_ground_item *item)
{
	t_ply *ply = game->ply;
	t_weapon *weap = &item->data.weap;

	for (int i = 0; i < ply->inventory.weap_count; i++)
	{
		if (ply->inventory.weapons[i].type == weap->type)
		{
			ply->inventory.weapons[i].ammo += weap->ammo;
			if (ply->inventory.weapons[i].ammo > MAX_AMMO)
				ply->inventory.weapons[i].ammo = MAX_AMMO;
			return;
		}
	}

	if (ply->inventory.weap_count < MAX_WEAPONS)
	{
		ply->inventory.weapons[ply->inventory.weap_count] = *weap;
		ply->inventory.weap_count += 1;
	}
}

/* Ajoute un outil à l’inventaire du joueur. */
static void pickup_tool(t_game *game, t_ground_item *item)
{
	t_ply *ply = game->ply;
	t_tool *tool = &item->data.tool;

	for (int i = 0; i < ply->inventory.tool_count; i++)
	{
		if (ply->inventory.tools[i].type == tool->type)
		{
			return;
		}
	}

	if (ply->inventory.tool_count < MAX_TOOLS)
	{
		ply->inventory.tools[ply->inventory.tool_count] = *tool;
		ply->inventory.tool_count += 1;
	}
}

/* Ramasse un objet selon son type. */
void pickup_item(t_game *game, t_ground_item *item)
{
	t_ply *ply = game->ply;
	if (!item)
		return;
	if (!is_near(ply->pos.x, ply->pos.y, item->pos_x, item->pos_y, item->pickup_range))
		return;

	if (item->type == ITEM_CONSUMABLE)
		pickup_consumable(game, item);
	else if (item->type == ITEM_WEAPON)
		pickup_weapon(game, item);
	else if (item->type == ITEM_TOOL)
		pickup_tool(game, item);

	game->flash_alpha = 0.5f;
	item->picked_up = 1;
}
