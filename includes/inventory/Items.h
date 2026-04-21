/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:16:00 by edurance          #+#    #+#             */
/*   Updated: 2026/04/21 12:38:30 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

#include <SDL.h>

#define MAX_ITEM_DIST_RENDER_SQ 400.0f

typedef struct s_ply t_ply;
typedef struct s_game t_game;

/* WEAPONS */
typedef enum	e_weapon_type
{
	WEAP_FISTS,
	WEAP_PISTOL,
	WEAP_SHOTGUN,
	WEAP_ROCKET_LAUNCHER
}			t_weapon_type;

typedef	struct	s_weapon
{
	t_weapon_type	type;
	int				ammo;
	
}				t_weapon;


/* CONSUMABLES (items on the floor) */
typedef enum	e_consumable_type
{
	CONS_HEAL,
	CONS_FUEL,
	CONS_BATTERY
}				t_consumable_type;

typedef struct	s_consumable
{
	t_consumable_type	type;
	int					amount;
}				t_consumable;


/* TOOLS */
typedef enum	e_tool_type
{
	TOOL_FLASHLIGHT,
	TOOL_KEY,
	TOOL_JETPACK
}				t_tool_type;

typedef struct	s_tool
{
	t_tool_type	type;
	union	u_data
	{
		int	battery;
		int	id;
		int	fuel;
	}		data;
}				t_tool;


typedef enum	e_proj_state
{
	PROJ_FLYING,
	PROJ_EXPLODING,
	PROJ_DEAD
}				t_proj_state;

typedef struct	s_projectile
{
	t_proj_state	state;

	float	x;
	float	y;
	float	target_x;
	float	target_y;
	float	speed;
	int		start_dist;
	int		size_x;
	int		size_y;

	SDL_Texture	*fly_texture;
	SDL_Rect	fly_dest;

	SDL_Texture	*expl_frames[3];
	int			expl_frame;
	int			expl_tick;
	int			expl_rate;

	struct	s_projectile	*next;
}			t_projectile;


/* ITEMS IN GENERAL */
typedef enum	s_item_type
{
	ITEM_CONSUMABLE,
	ITEM_WEAPON,
	ITEM_TOOL
}				t_item_type;

typedef union	u_item_data
{
	t_consumable	cons;
	t_weapon		weap;
	t_tool			tool;
}				t_item_data;

/* ITEMS ON THE GROUND */
typedef struct	s_ground_item
{
	t_item_type			type;
	t_item_data			data;

	float			pos_x;
	float			pos_y;
	float			pos_z;
	float			pickup_range;
	int				picked_up;

	float			world_height;
	float			aspect_ratio;

	char			*texture_path;
	SDL_Texture		*texture;
	int				w;
	int				h;
}				t_ground_item;

int		is_near(float px, float py, float ix, float iy, float range);
void	pickup_item(t_game *game, t_ground_item *item);
void	update_item(t_game *game);
void	pickup_flash(t_game *game);
void	render_items(t_game *game);
void	cleanup_items(t_game *game);
void	spawn_rocket(t_game *game, float tx, float ty);
void	update_projectiles(t_game *game);
void	render_projectiles(t_game *game);
void	add_item(t_game *game, t_ground_item new_item);

#endif
