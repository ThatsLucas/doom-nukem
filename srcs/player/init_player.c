/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:27:57 by edurance          #+#    #+#             */
/*   Updated: 2026/10/29 10:36:56 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.h"
#include "Game.h"

/* Ajoute les armes de départ à l’inventaire du joueur. */
static void give_starter_weapons(t_ply *ply)
{
	t_weapon fists = {
		.type = WEAP_FISTS,
		.ammo = -1};
	ply->inventory.weapons[ply->inventory.weap_count++] = fists;

	t_weapon pistol = {
		.type = WEAP_PISTOL,
		.ammo = 50};
	ply->inventory.weapons[ply->inventory.weap_count++] = pistol;
}

/* Ajoute les outils de départ à l’inventaire du joueur. */
static void give_starter_tools(t_ply *ply)
{
	//t_tool flashlight = {
	//	.type = TOOL_FLASHLIGHT,
	//	.data.battery = 11,
	//	.using = 0};
	//ply->inventory.tools[ply->inventory.tool_count++] = flashlight;

	t_tool jetpack = {
		.type = TOOL_JETPACK,
		.data.fuel = 11,
		.using = 0};
	ply->inventory.tools[ply->inventory.tool_count++] = jetpack;
	ply->inventory.jetpack = &ply->inventory.tools[ply->inventory.tool_count - 1];
}

/* Configure l’équipement de départ du joueur. */
static void config_starter(t_ply *ply)
{
	give_starter_weapons(ply);
	give_starter_tools(ply);
	ply->held_weap = &ply->inventory.weapons[ply->current_weap_index];
}

void reset_player(t_game *game)
{
	t_ply *ply = game->ply;

	ft_bzero(&ply->keys, sizeof(t_keys));
	ft_bzero(&ply->inventory, sizeof(t_inventory));
	ply->pitch = 0;
	ply->dir_z = 0.0f;
	ply->crosshair_target = NULL;
	ply->current_weap_index = 0;
	ply->hp = 100;

	/*physics*/
	ply->physic.gravity = DEFAULT_GRAVITY;
	ply->physic.velocity = 0;
	ply->physic.is_on_ground = 1;
	ply->physic.last_time = 0;
	ply->physic.is_running = 0;
	ply->physic.is_crouching = 0;
	ply->physic.speed = 0.03f;

	config_starter(ply);
}

/* Initialise le joueur : position, santé et équipement de départ. */
void init_player(t_game *game, float pos_x, float pos_y, float dir_x, float dir_y)
{
	t_ply *ply;
	float FOV = game->settings.FOV;

	ply = calloc(1, sizeof(t_ply));
	if (!ply)
		exit_game(game, "player allocation");

	ply->pos.x = pos_x;
	ply->pos.y = pos_y;
	ply->floor_height = 0.0f;
	ply->ceiling_height = 0.0f;
	ply->dir_z = 0.0f;

	ply->dir.x = dir_x;
	ply->dir.y = dir_y;

	ply->plane.x = -ply->dir.y * FOV;
	ply->plane.y = ply->dir.x * FOV;

	game->ply = ply;
	reset_player(game);
}
