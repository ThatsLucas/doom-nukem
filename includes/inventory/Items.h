/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:16:00 by edurance          #+#    #+#             */
/*   Updated: 2026/10/20 13:52:09 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

# include <SDL.h>

# define MAX_ITEM_DIST_RENDER_SQ 400.0f
# define FISTS_DAMAGE 25
# define PISTOL_DAMAGE 50
# define SHOTGUN_DAMAGE 100
# define ROCKET_DAMAGE 200

typedef struct s_ply	t_ply;
typedef struct s_game	t_game;
typedef struct s_vect2	t_vect2;

/* WEAPONS */
typedef enum e_weapon_type
{
	WEAP_FISTS,
	WEAP_PISTOL,
	WEAP_SHOTGUN,
	WEAP_ROCKET_LAUNCHER
}						t_weapon_type;

typedef struct s_weapon
{
	t_weapon_type		type;
	int					ammo;

}						t_weapon;

/* CONSUMABLES (items on the floor) */
typedef enum e_consumable_type
{
	CONS_HEAL,
	CONS_FUEL,
	CONS_BATTERY
}						t_consumable_type;

typedef struct s_consumable
{
	t_consumable_type	type;
	int					amount;
}						t_consumable;

/* TOOLS */
typedef enum e_tool_type
{
	TOOL_FLASHLIGHT,
	TOOL_KEY,
	TOOL_JETPACK
}						t_tool_type;

typedef struct s_tool
{
	t_tool_type			type;
	int					using;
	union				u_data
	{
		int				battery;
		int				id;
		int				fuel;
	} data;
}						t_tool;

typedef enum e_proj_state
{
	PROJ_FLYING,
	PROJ_EXPLODING,
	PROJ_DEAD
}						t_proj_state;

typedef struct s_projectile
{
	t_proj_state		state;

	float				x;
	float				y;
	float				target_x;
	float				target_y;
	float				speed;
	int					start_dist;
	int					size_x;
	int					size_y;

	SDL_Texture			*fly_texture;
	SDL_Rect			fly_dest;

	SDL_Texture			*expl_frames[3];
	int					expl_frame;
	int					expl_tick;
	int					expl_rate;

	struct s_projectile	*next;
}						t_projectile;

/* ITEMS IN GENERAL */
typedef enum s_item_type
{
	ITEM_CONSUMABLE,
	ITEM_WEAPON,
	ITEM_TOOL
}						t_item_type;

typedef union u_item_data
{
	t_consumable		cons;
	t_weapon			weap;
	t_tool				tool;
}						t_item_data;

/* ITEMS ON THE GROUND */
typedef struct s_ground_item
{
	t_item_type			type;
	t_item_data			data;

	float				pos_x;
	float				pos_y;
	float				pos_z;
	float				pickup_range;
	int					picked_up;

	float				world_height;
	float				aspect_ratio;

	char				*texture_path;
	SDL_Texture			*texture;
	int					w;
	int					h;
}						t_ground_item;

int						is_near(float px, float py, float ix, float iy,
							float range);
void					pickup_item(t_game *game, t_ground_item *item);
void					update_item(t_game *game);
void					pickup_flash(t_game *game);
void					render_items(t_game *game);
void					cleanup_items(t_game *game);
void					spawn_rocket(t_game *game, float tx, float ty);
void					update_projectiles(t_game *game);
void					render_projectiles(t_game *game);
void					activate_flashlight(t_game *game);
void					activate_jetpack(t_game *game);
void					add_item(t_game *game, t_ground_item new_item);

void					create_ground_item(t_game *game, t_vect2 pos,
							char *png_path, float world_height, t_ground_item item);
void					create_item_heal(t_game *game, t_vect2 pos, int amount);
void					create_item_fuel(t_game *game, t_vect2 pos, int amount);
void					create_item_battery(t_game *game, t_vect2 pos, int amount);
void					create_item_pistol(t_game *game, t_vect2 pos, int ammo);
void					create_item_shotgun(t_game *game, t_vect2 pos, int ammo);
void					create_item_rocket_launcher(t_game *game, t_vect2 pos, int ammo);
void					create_item_flashlight(t_game *game, t_vect2 pos);
void					create_item_key(t_game *game, t_vect2 pos, int id);
void					create_item_jetpack(t_game *game, t_vect2 pos);

#endif
