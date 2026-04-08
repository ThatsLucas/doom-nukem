/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:21:26 by edurance          #+#    #+#             */
/*   Updated: 2026/04/08 12:07:12 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "inventory/Inventory.h"

typedef struct s_game t_game;

typedef struct	s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
}			t_keys;

typedef struct s_ply
{
	/* events */
	float		pos_x;
	float		pos_y;
	float		dir_x;
	float		dir_y;
	float		dir_z;
	t_keys		keys;

	/* attributs */
	t_inventory	inventory;
	int			hp;
}				t_ply;

void	init_player(t_game *game, float pos_x, float pos_y, float dir_x, float dir_y);

# endif
