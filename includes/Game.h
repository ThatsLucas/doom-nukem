/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:59:25 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/13 20:32:52 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include <pthread.h>
#include <SDL.h>
#include <sys/time.h>
#include <pthread.h>
#include "Window.h"
#include "Player.h"
#include "../libft/include/libft.h"
#include "Raycasting/Raycasting.h"
#include "Raycasting/Types.h"

# ifndef M_PI
#  define M_PI 3.14159265359f
# endif

typedef struct s_ply t_ply;

typedef struct s_game
{
	int			status;			// 0 = mainPage, -1 = editor, >0 = gameLevel
	t_ply		*ply;
	t_WIN		*window;
	int			mapSize[2];
	int			screenSize[2];
	t_map		*map;
	SDL_Texture	*frame;
	Uint32		*frame_buffer;
	t_ray		*rays;
	char		*fps;
}				t_game;

/*init/exit game*/
void	exit_game(t_game *game, char *type);
t_game	*init_game(void);
void	free_map(t_map *map);
t_map	*init_test_map(void);

/*utils*/
float	to_pixelX(float x, t_game *game);
float	to_pixelY(float y, t_game *game);
float	to_PosX(float x, t_game *game);
float	to_PosY(float y, t_game *game);
void	precompute_mirrors(t_map *map);

#endif
