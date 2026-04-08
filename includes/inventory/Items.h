/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:16:00 by edurance          #+#    #+#             */
/*   Updated: 2026/04/08 11:28:31 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

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

#endif
