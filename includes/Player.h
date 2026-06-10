/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:21:26 by edurance          #+#    #+#             */
/*   Updated: 2026/06/10 16:46:07 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
#define PLAYER_H

#include "inventory/Inventory.h"
#include "Raycasting/Types.h"
#include "entities/Entities.h"

#define MAX_HP 100
#define MAX_AMMO 800
#define MAX_BATTERY 100
#define MAX_FUEL 100
#define INFINITE_AMMO -1

typedef struct s_game t_game;
typedef struct s_vect2 t_vect2;
typedef struct s_inventory t_inventory;

typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
	int e;
	int left;
	int right;
} t_keys;

#define DEFAULT_GRAVITY 9.8 // gravite terrestre

typedef struct s_ply_physics
{
	Uint64 Curtime;
	Uint64 last_time;
	float velocity;
	float gravity;
	int is_on_ground;
	int is_running;
} t_ply_physics;

typedef struct s_ply
{
	/* events */
	t_vect2 pos;
	float floor_height;
	float ceiling_height;
	float z;
	t_vect2 dir;
	float dir_z;
	t_keys keys;
	int pitch;
	int sector;
	t_vect2 plane;

	t_entity *crosshair_target;

	/* attributs */
	t_inventory inventory;
	t_weapon *held_weap;
	int current_weap_index;
	int hp;

	/*physic*/
	t_ply_physics physic;
} t_ply;

void init_player(t_game *game, float pos_x, float pos_y, float dir_x, float dir_y);

/*Physics*/
float get_delta_time(t_ply *ply);
void player_jump(t_game *game);
void apply_constant_forces_to_player(t_ply *ply);
void use_jetpack(t_ply *ply);

#endif
