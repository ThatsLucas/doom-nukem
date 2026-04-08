/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:27:57 by edurance          #+#    #+#             */
/*   Updated: 2026/04/08 12:02:08 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.h"
#include "Game.h"

/* Add starter pack to begin a mission */
static void	config_starter(t_ply	*ply)
{
	t_weapon	pistol = {
		.type = WEAP_PISTOL,
		.ammo = 50
	};
	ply->inventory.weapons[ply->inventory.weap_count++] = pistol;

	t_tool	jetpack = {
		.type = TOOL_JETPACK,
		.data.fuel = 100
	};
	ply->inventory.tools[ply->inventory.tool_count++] = jetpack;
}

/* 
	Initialize the player with default direction and position.
	Adds default health (100 max).
	Adds default weapons and tools with config starter.
*/
void	init_player(t_game *game, float pos_x, float pos_y, float dir_x, float dir_y)
{
	t_ply	*ply;

	ply = malloc(sizeof(t_ply));
	if (!ply)
		exit_game(game, "player allocation");

	ply->pos_x = pos_x;
	ply->pos_y = pos_y;
	ply->dir_x = dir_x;
	ply->dir_y = dir_y;
	ply->dir_z = 0.0f;

	ft_bzero(&ply->keys, sizeof(t_keys));

	ply->inventory.weap_count = 0;
	ply->inventory.tool_count = 0;
	ft_bzero(ply->inventory.tools,sizeof(ply->inventory.tools));
	ft_bzero(ply->inventory.weapons, sizeof(ply->inventory.weapons));

	ply->hp = 100;

	config_starter(ply);
	game->ply = ply;
}
