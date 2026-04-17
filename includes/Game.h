/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:59:25 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/17 11:13:31 by edurance         ###   ########.fr       */
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
#include "GUI/GUI.h"
#include "parser/PNG.h"
#include "../libft/include/libft.h"
#include "Raycasting/Raycasting.h"
#include "Raycasting/Types.h"

# ifndef M_PI
#  define M_PI 3.14159265359f
# endif

# ifndef EYES_HEIGTH
#  define EYES_HEIGTH 1.6
# endif

# ifndef FOV
#  define FOV 0.80
# endif

# ifndef RAYCAST_THREADS
#  define RAYCAST_THREADS 8
# endif


typedef struct s_ply t_ply;

typedef struct	s_game
{
	t_ply			*ply;
	t_WIN			*window;
	t_ground_item	items[10];
	t_projectile	*projectiles;
	int				items_count;
	float			flash_alpha;
	t_hud_cache		hud_cache;
	int				screenSize[2];
	int				status;			// 0 = mainPage, -1 = editor, >0 = gameLevel
	int				mapSize[2];
	t_map			*map;
	SDL_Texture		*frame;
	Uint32			*frame_buffer;
	t_ray			*rays;
	char			*fps;
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
