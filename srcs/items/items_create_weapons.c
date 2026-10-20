/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_create_weapons.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 12:58:20 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 12:58:20 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "inventory/Items.h"

/* Crée l’objet pistolet. */
void	create_item_pistol(t_game *game, t_vect2 pos, int ammo)
{
	t_ground_item	item;

	item.type = ITEM_WEAPON;
	item.data.weap.type = WEAP_PISTOL;
	item.data.weap.ammo = ammo;
	create_ground_item(game, pos, "assets/png/items/weapons/pistol.png", 0.35f, item);
}

/* Crée l’objet fusil à pompe. */
void	create_item_shotgun(t_game *game, t_vect2 pos, int ammo)
{
	t_ground_item	item;

	item.type = ITEM_WEAPON;
	item.data.weap.type = WEAP_SHOTGUN;
	item.data.weap.ammo = ammo;
	create_ground_item(game, pos, "assets/png/items/weapons/shotgun.png", 0.35f, item);
}

/* Crée l’objet lance-roquettes. */
void	create_item_rocket_launcher(t_game *game, t_vect2 pos, int ammo)
{
	t_ground_item	item;

	item.type = ITEM_WEAPON;
	item.data.weap.type = WEAP_ROCKET_LAUNCHER;
	item.data.weap.ammo = ammo;
	create_ground_item(game, pos, "assets/png/items/weapons/rocket_launcher.png", 0.35f, item);
}
