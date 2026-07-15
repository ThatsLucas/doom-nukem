/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:21:26 by edurance          #+#    #+#             */
/*   Updated: 2026/07/15 17:43:37 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
#define PLAYER_H

#include "inventory/Inventory.h"
#include "Raycasting/Types.h"
# include "entities/Entities.h"

#define MAX_HP 100
#define MAX_AMMO 800
#define MAX_BATTERY 11
#define MAX_FUEL 11
#define INFINITE_AMMO -1

typedef struct	s_game t_game;
typedef struct	s_vect2 t_vect2;
typedef struct	s_inventory t_inventory;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		e;
	int		left;
	int		right;
}			t_keys;

typedef struct s_ply
{
	/* events */
	t_vect2		pos;
	float		z;
	t_vect2		dir;
	float		dir_z;
	t_keys		keys;
	int			pitch;
	int			sector;
	t_vect2		plane;

	t_entity	*crosshair_target;

	/* attributs */
	t_inventory inventory;
	t_weapon *held_weap;
	int current_weap_index;
	int hp;
} t_ply;

void init_player(t_game *game, float pos_x, float pos_y, float dir_x, float dir_y);

#endif
