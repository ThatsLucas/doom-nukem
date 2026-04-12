/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:59:25 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/12 11:27:49 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include <SDL.h>
#include <sys/time.h>
#include "Window.h"
#include "../libft/include/libft.h"
#include "Raycasting/Raycasting.h"
#include "Raycasting/Types.h"

# ifndef M_PI
#  define M_PI 3.14159265359f
# endif

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
	t_vect2		pos;
	t_vect2		dir;
	t_keys		keys;
	int			pitch;
}				t_ply;

typedef struct s_game
{
	int			status;			// 0 = mainPage, -1 = editor, >0 = gameLevel
	t_ply		*ply;
	t_WIN		*window;
	int			mapSize[2];
	int			screenSize[2];
	t_list		*walls;
	t_bsp		*bspTree;
	SDL_Surface	*surface[4];
	t_RGB		**text_colors;
	SDL_Texture	*frame;
	Uint32		*frame_buffer;
	t_ray		*rays;
	char		*fps;
}				t_game;

/*init/exit game*/
void	exit_game(t_game *game, char *type);
t_game	*init_game(void);

/*utils*/
float	to_pixelX(float x, t_game *game);
float	to_pixelY(float y, t_game *game);
float	to_PosX(float x, t_game *game);
float	to_PosY(float y, t_game *game);

void	add_wall(t_game *game, float transparency);
void	rm_last_wall(t_game *game);

#endif
