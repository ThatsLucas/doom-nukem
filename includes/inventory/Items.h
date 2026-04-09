/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:16:00 by edurance          #+#    #+#             */
/*   Updated: 2026/04/09 10:46:03 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

#include <SDL.h>

typedef struct s_ply t_ply;
typedef struct s_game t_game;

typedef enum	e_weapon_type
{
	WEAP_PISTOL,
	WEAP_SHOTGUN,
	WEAP_ROCKET_LAUNCHER
}			t_weapon_type;

typedef	struct	s_weapon
{
	t_weapon_type	type;
	int				ammo;
	
}				t_weapon;

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

typedef struct	s_ground_item
{
	t_item_type			type;
	t_item_data			data;

	float			pos_x;
	float			pos_y;
	char			*texture_path;
	SDL_Texture		*texture;
	int				w;
	int				h;
	float			pickup_range;
}				t_ground_item;

int		is_near(float px, float py, float ix, float iy, float range);
void	pickup_item(t_game *game, t_ground_item *item);
void	update_item(t_game *game);
void	pickup_flash(t_game *game);
void	render_items(t_game *game);
void	cleanup_items(t_game *game);

#endif
