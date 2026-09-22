/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 12:40:27 by edurance          #+#    #+#             */
/*   Updated: 2026/09/22 12:40:27 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 00:00:00 by edurance          #+#    #+#             */
/*   Updated: 2026/09/22 00:00:00 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "inventory/Items.h"

#define ITEM_PICKUP_RANGE 1.2f

/* fonction de fabrique commune */
static void	create_ground_item(t_game *game, t_vect2 pos, char *png_path,
				float world_height, t_ground_item item)
{
	t_png	png;
	int		sector;

	sector = find_sector(game->map, pos);
	if (sector == -1)
		exit_game(game, "Failed to find sector for item");
	item.pos_x = pos.x;
	item.pos_y = pos.y;
	item.pos_z = get_plane_z(game->map->sectors[sector].floor_plane,
			pos.x, pos.y);
	item.pickup_range = ITEM_PICKUP_RANGE;
	item.picked_up = 0;
	item.world_height = world_height;

	png.w = 0;
	png.h = 0;
	png.path = ft_strdup(png_path);
	if (!png.path)
		exit_game(game, "Failed to strdup item texture path");
	if (!process_png(&png))
		exit_game(game, "Failed to load item texture");
	item.texture = create_image(&png, game->window->renderPTR);
	if (!item.texture)
		exit_game(game, "Failed to create item image");
	item.texture_path = png_path;
	item.w = (int)png.w;
	item.h = (int)png.h;
	item.aspect_ratio = (float)item.w / (float)item.h;

	add_item(game, item);
}

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

/* pistol */
void	create_item_pistol(t_game *game, t_vect2 pos, int ammo)
{
	t_ground_item	item;

	item.type = ITEM_WEAPON;
	item.data.weap.type = WEAP_PISTOL;
	item.data.weap.ammo = ammo;
	create_ground_item(game, pos, "assets/png/items/weapons/pistol.png", 0.35f, item);
}

/* shotgun */
void	create_item_shotgun(t_game *game, t_vect2 pos, int ammo)
{
	t_ground_item	item;

	item.type = ITEM_WEAPON;
	item.data.weap.type = WEAP_SHOTGUN;
	item.data.weap.ammo = ammo;
	create_ground_item(game, pos, "assets/png/items/weapons/shotgun.png", 0.35f, item);
}

/* rocket launcher */
void	create_item_rocket_launcher(t_game *game, t_vect2 pos, int ammo)
{
	t_ground_item	item;

	item.type = ITEM_WEAPON;
	item.data.weap.type = WEAP_ROCKET_LAUNCHER;
	item.data.weap.ammo = ammo;
	create_ground_item(game, pos, "assets/png/items/weapons/rocket_launcher.png", 0.35f, item);
}

/* flashlight */
void	create_item_flashlight(t_game *game, t_vect2 pos)
{
	t_ground_item	item;

	item.type = ITEM_TOOL;
	item.data.tool.type = TOOL_FLASHLIGHT;
	item.data.tool.using = 0;
	item.data.tool.data.battery = 0;
	create_ground_item(game, pos, "assets/png/hud/tools/flashlight.png", 0.3f, item);
}

/* key */
void	create_item_key(t_game *game, t_vect2 pos, int id)
{
	t_ground_item	item;

	item.type = ITEM_TOOL;
	item.data.tool.type = TOOL_KEY;
	item.data.tool.using = 0;
	item.data.tool.data.id = id;
	create_ground_item(game, pos, "assets/png/hud/tools/key.png", 0.25f, item);
}

/* jetpack */
void	create_item_jetpack(t_game *game, t_vect2 pos)
{
	t_ground_item	item;

	item.type = ITEM_TOOL;
	item.data.tool.type = TOOL_JETPACK;
	item.data.tool.using = 0;
	item.data.tool.data.fuel = 0;
	create_ground_item(game, pos, "assets/png/items/tools/jetpack.png", 0.6f, item);
}

