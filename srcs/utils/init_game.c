/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 16:25:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/12 15:53:18 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

static void load_settings(t_game *game)
{
	game->settings.FOV = DEFAULT_FOV;
	game->settings.MouseSensibility = DEFAULT_MOUSE_SENSIBILITY;
	game->settings.move_forward = 'w';
	game->settings.move_backward = 's';
	game->settings.move_left = 'a';
	game->settings.move_right = 'd';
}

/* TTF, SDL, window and menu images */
static void init_window(t_game *game)
{
	if (TTF_Init() < 0)
		exit_game(game, "TTF Init");

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS))
		exit_game(game, "SDL_INIT");
	get_screen_size(&game->screenSize[0], &game->screenSize[1]);
	game->window = create_window("Doom Nukem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game->screenSize[0], game->screenSize[1], SDL_WINDOW_OPENGL);
	if (!game->window)
		exit_game(game, "create_window");
	if (!init_all_imgs(game, game->window))
	{
		exit_game(game, "Img Loading\n");
	}
	game->window->menus.main.has_init = 1;
}

/* Frame buffer, z buffer, rays and the streaming texture of the frame */
static void init_buffers(t_game *game)
{
	game->frame_buffer = calloc(game->screenSize[0] * game->screenSize[1], sizeof(Uint32));
	game->z_buffer = malloc(game->screenSize[0] * game->screenSize[1] * sizeof(float));
	game->rays = calloc(game->screenSize[0], sizeof(t_ray));
	game->fps = NULL;
	game->frame = SDL_CreateTexture(game->window->renderPTR,
									SDL_PIXELFORMAT_ARGB8888,
									SDL_TEXTUREACCESS_STREAMING,
									game->screenSize[0],
									game->screenSize[1]);
	if (!game->frame_buffer || !game->z_buffer || !game->rays || !game->frame)
		exit_game(game, "game malloc (frames)");
}

static void init_world(t_game *game)
{
	init_entities(&game->entities);
	game->items = malloc(sizeof(t_ground_item) * 16);
	if (!game->items)
		exit_game(game, "failed malloc items");
	game->items_count = 0;
	game->items_capacity = 16;
}

t_game *init_game(void)
{
	t_game *game;

	game = calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	load_settings(game);
	game->selected_language = 0;
	parse_languages(game, game->selected_language); // english par defaut
	init_window(game);

	init_hud_cache(game);
	init_player(game, 500, 500, 0.0f, 1.0f);
	if (TTF_Init() < 0)
		exit_game(game, "TTF Init");

	init_buffers(game);
	game->window->menus.notif.notif_buf = NULL;
	game->window->menus.current = 1;

	game->minimap_tex = SDL_CreateTexture(game->window->renderPTR, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);

	init_world(game);
	game->is_paused = 0;
	init_editor(game);

	return (game);
}
