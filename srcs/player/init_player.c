/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:27:57 by edurance          #+#    #+#             */
/*   Updated: 2026/08/11 14:21:09 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.h"
#include "Game.h"

/* Add starter pack to begin a mission */
static void config_starter(t_ply *ply)
{
	t_weapon fists = {
		.type = WEAP_FISTS,
		.ammo = -1};
	ply->inventory.weapons[ply->inventory.weap_count++] = fists;

	t_weapon pistol = {
		.type = WEAP_PISTOL,
		.ammo = 50};
	ply->inventory.weapons[ply->inventory.weap_count++] = pistol;

	t_weapon shotgun = {
		.type = WEAP_SHOTGUN,
		.ammo = 50};
	ply->inventory.weapons[ply->inventory.weap_count++] = shotgun;

	t_weapon rocket = {
		.type = WEAP_ROCKET_LAUNCHER,
		.ammo = 50};
	ply->inventory.weapons[ply->inventory.weap_count++] = rocket;

	t_tool flashlight = {
		.type = TOOL_FLASHLIGHT,
		.data.battery = 11,
		.using = 0};
	ply->inventory.tools[ply->inventory.tool_count++] = flashlight;

	t_tool key = {
		.type = TOOL_KEY,
		.data.id = 11,
		.using = 0};
	ply->inventory.tools[ply->inventory.tool_count++] = key;

	t_tool jetpack = {
		.type = TOOL_JETPACK,
		.data.fuel = 11,
		.using = 0};
	ply->inventory.tools[ply->inventory.tool_count++] = jetpack;
	ply->inventory.jetpack = &ply->inventory.tools[ply->inventory.tool_count - 1];

	ply->held_weap = &ply->inventory.weapons[ply->current_weap_index];
}

/*
	Initialize the player with default direction and position.
	Adds default health (100 max).
	Adds default weapons and tools with config starter.
*/
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
	game->ply = ply;
}
