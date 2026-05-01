/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:27:57 by edurance          #+#    #+#             */
/*   Updated: 2026/04/17 12:12:02 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.h"
#include "Game.h"

/* Add starter pack to begin a mission */
static void	config_starter(t_ply	*ply)
{
	t_weapon	fists = {
		.type = WEAP_FISTS,
		.ammo = -1
	};
	ply->inventory.weapons[ply->inventory.weap_count++] = fists;

	t_weapon	pistol = {
		.type = WEAP_PISTOL,
		.ammo = 5
	};
	ply->inventory.weapons[ply->inventory.weap_count++] = pistol;

	t_weapon	shotgun = {
		.type = WEAP_SHOTGUN,
		.ammo = 50
	};
	ply->inventory.weapons[ply->inventory.weap_count++] = shotgun;

	t_weapon	rocket = {
		.type = WEAP_ROCKET_LAUNCHER,
		.ammo = 50
	};
	ply->inventory.weapons[ply->inventory.weap_count++] = rocket;

	t_tool	jetpack = {
		.type = TOOL_JETPACK,
		.data.fuel = 40
	};
	ply->inventory.tools[ply->inventory.tool_count++] = jetpack;

	ply->held_weap = &ply->inventory.weapons[ply->current_weap_index];
}

/* 
	Initialize the player with default direction and position.
	Adds default health (100 max).
	Adds default weapons and tools with config starter.
*/
void	init_player(t_game *game, float pos_x, float pos_y, float dir_x, float dir_y)
{
	t_ply	*ply;

	ply = calloc(1, sizeof(t_ply));
	if (!ply)
		exit_game(game, "player allocation");

	ply->pos_x = pos_x;
	ply->pos_y = pos_y;
	ply->dir_x = dir_x;
	ply->dir_y = dir_y;
	ply->dir_z = 0.0f;

	ply->hp = 15;

	config_starter(ply);
	game->ply = ply;
}
