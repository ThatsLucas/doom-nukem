/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:59:25 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/15 12:02:07 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include <pthread.h>
#include <SDL.h>
#include "Window.h"
#include "Player.h"
#include "GUI/GUI.h"
#include "parser/PNG.h"
#include "../libft/include/libft.h"
# ifndef M_PI
#  define M_PI 3.14159265359f
# endif

typedef struct s_ply t_ply;

typedef struct s_game
{
	t_ply			*ply;
	t_WIN			*window;
	t_ground_item	items[10];
	t_projectile	*projectiles;
	int				items_count;
	float			flash_alpha;
	t_hud_cache		hud_cache;
	int				screenSize[2];
}				t_game;

void	exit_game(t_game *game, char *type);
t_game	*init_game(void);

#endif
