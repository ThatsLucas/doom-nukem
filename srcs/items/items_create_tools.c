/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_create_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 12:58:20 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 12:58:20 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "inventory/Items.h"

/* Crée l’objet lampe torche. */
void	create_item_flashlight(t_game *game, t_vect2 pos)
{
	t_ground_item	item;

	item.type = ITEM_TOOL;
	item.data.tool.type = TOOL_FLASHLIGHT;
	item.data.tool.using = 0;
	item.data.tool.data.battery = 0;
	create_ground_item(game, pos, "assets/png/hud/tools/flashlight.png", 0.3f, item);
}

/* Crée l’objet clé. */
void	create_item_key(t_game *game, t_vect2 pos, int id)
{
	t_ground_item	item;

	item.type = ITEM_TOOL;
	item.data.tool.type = TOOL_KEY;
	item.data.tool.using = 0;
	item.data.tool.data.id = id;
	create_ground_item(game, pos, "assets/png/hud/tools/key.png", 0.25f, item);
}

/* Crée l’objet jetpack. */
void	create_item_jetpack(t_game *game, t_vect2 pos)
{
	t_ground_item	item;

	item.type = ITEM_TOOL;
	item.data.tool.type = TOOL_JETPACK;
	item.data.tool.using = 0;
	item.data.tool.data.fuel = 0;
	create_ground_item(game, pos, "assets/png/items/tools/jetpack.png", 0.6f, item);
}
