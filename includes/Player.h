/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:21:26 by edurance          #+#    #+#             */
/*   Updated: 2026/04/16 23:35:55 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define MAX_WEAPONS 3
# define MAX_TOOLS 3

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
	CONS_AMMO
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

typedef struct	s_inventory
{
	t_weapon	weapons[MAX_WEAPONS];
	int			weap_count;

	t_tool		tools[MAX_TOOLS];
	int			tool_count;
}				t_inventory;

typedef struct	s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}			t_keys;

typedef struct s_ply
{
	/* events */
	t_vect2		pos;
	float		z;
	t_vect2		dir;
	t_keys		keys;
	int			pitch;
	int			sector;

	/* attributs */
	t_inventory	inventory;
	int			hp;
}				t_ply;

# endif
