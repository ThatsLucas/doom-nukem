/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:59:25 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:13:16 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include <pthread.h>
#include <SDL.h>
#include <sys/time.h>
#include "Window.h"
#include "Player.h"
#include "GUI/GUI.h"
#include "parser/PNG.h"
#include "../libft/include/libft.h"
#include "Raycasting/Raycasting.h"
#include "Raycasting/Types.h"
#include "languages/language.h"
#include "multiplayer/client.h"
#include "multiplayer/server.h"
#include "entities/Entities.h"
#include "Editor.h"

#ifndef M_PI
#define M_PI 3.14159265359f
#endif

#ifndef EYES_HEIGTH
#define EYES_HEIGTH 1.6
#endif

#ifndef STEP_HEIGHT
#define STEP_HEIGHT 0.5
#endif

#ifndef HEAD_MARGIN // marge pour passer un portail
#define HEAD_MARGIN 0.2
#endif

/*FOV*/

#ifndef MIN_FOV // jamais negatif
#define MIN_FOV 0.80
#endif

#ifndef MAX_FOV
#define MAX_FOV 1.80
#endif

#ifndef DEFAULT_FOV
#define DEFAULT_FOV (MAX_FOV + MIN_FOV) / 2
#endif

/*Mouse Sensibility*/

#ifndef MIN_MOUSE_SENSIBILITY // jamais negatif
#define MIN_MOUSE_SENSIBILITY 0.0001
#endif

#ifndef MAX_MOUSE_SENSIBILITY
#define MAX_MOUSE_SENSIBILITY 0.004
#endif

#ifndef DEFAULT_MOUSE_SENSIBILITY
#define DEFAULT_MOUSE_SENSIBILITY (MAX_MOUSE_SENSIBILITY + MIN_MOUSE_SENSIBILITY) / 2
#endif

#ifndef RAYCAST_THREADS
#define RAYCAST_THREADS 8
#endif

#ifndef ELEVATOR_SPEED
# define ELEVATOR_SPEED 1.0f	/* unites par seconde */
#endif

typedef struct s_ply t_ply;

typedef struct s_settings
{
	float FOV;
	float MouseSensibility;
	int move_forward;
	int move_backward;
	int move_left;
	int move_right;
	int multiplayer_enabled;
} t_settings;

typedef struct s_game
{
	t_ply *ply;
	t_WIN *window;
	int current_level;
	t_projectile *projectiles;
	float flash_alpha;
	t_hud_cache hud_cache;
	int screenSize[2];
	int status;		// 0 = mainPage, -1 = editor, >0 = gameLevel
	SDL_Texture *minimap_tex;
	t_map *map;
	SDL_Texture *frame;
	Uint32 *frame_buffer;
	t_ray *rays;
	char *fps;
	t_settings settings;
	int selected_language;
	t_languages *languages;
	double delta_time;
	pthread_t serverThread;
	t_udp_connections clientConnection;
	t_udp_server_status serverStatus;

	t_ground_item	*items;
	int				items_count;
	int				items_capacity;
	t_entities		entities;
	t_editor		*editor;
	int is_paused;
}				t_game;

/*init/exit game*/
void exit_game(t_game *game, char *type);
t_game *init_game(void);
void free_map(t_map *map);

/*utils*/
long get_timestamp(void);
float to_pixelX(float x, t_game *game);
float to_pixelY(float y, t_game *game);
float to_PosX(float x, t_game *game);
float to_PosY(float y, t_game *game);
int init_all_imgs(t_game *game, t_WIN *win);
void display_fps_periodic(Uint64 start);

void render_entities(t_game *game);
int	find_sector(t_map *map, t_vect2 p);
int	find_sector_z(t_map *map, t_vect2 p, float z);

#endif
