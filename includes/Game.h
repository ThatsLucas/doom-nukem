/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:59:25 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/08 13:01:14 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include <SDL.h>
#include "Window.h"
#include "../libft/include/libft.h"
#include "Raycasting.h"

# ifndef M_PI
#  define M_PI 3.14159265359f
# endif

typedef struct	s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
}			t_keys;

typedef struct s_ply
{
	t_vect2		pos;
	t_vect2		dir;
	t_keys		keys;
}				t_ply;

typedef struct s_game
{
	t_ply		*ply;
	t_WIN		*window;
	int			mapSize[2];
	int			screenSize[2];
}				t_game;

void	exit_game(t_game *game, char *type);
t_game	*init_game(void);
float	to_pixelX(float x, t_game *game);
float	to_pixelY(float y, t_game *game);
void	draw_wall(t_game *game, t_vect2 a, t_vect2 b);

#endif
