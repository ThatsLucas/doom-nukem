/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 16:25:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/22 17:06:31 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

static void load_settings(t_game *game)
{
	game->settings.FOV = DEFAULT_FOV;
	game->settings.move_forward = 'w';
	game->settings.move_backward = 's';
	game->settings.move_left = 'a';
	game->settings.move_right = 'd';
}

void	init_textures(t_game *game, t_map *map)
{
	SDL_Surface	*surface;
	SDL_Surface *converted;

	char *assets[4] = {"assets/east.bmp", "assets/west.bmp", "assets/north.bmp", "assets/south.bmp"};

	map->textures = calloc(4, sizeof(t_tex));
	if (!map->textures)
			exit_game(game, "init_textures");
	map->cap_textures = 4;
	for (int i = 0; i < 4; i++)
	{
		map->num_textures++;
		surface = SDL_LoadBMP(assets[i]);
		if (!surface)
			exit_game(game, "init_textures");
		converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
		map->textures[i].colors = malloc(sizeof(t_RGB) * converted->w * converted->h);
		if (!map->textures[i].colors)
			exit_game(game, "init_textures");
		Uint32 *pixels = (Uint32 *)converted->pixels;
		for (int j = 0; j < converted->w * converted->h; j++)
			SDL_GetRGB(pixels[j], converted->format, &map->textures[i].colors[j].r,
			&map->textures[i].colors[j].g, &map->textures[i].colors[j].b);
		map->textures[i].w = converted->w;
		map->textures[i].h = converted->h;
		SDL_FreeSurface(converted);
		SDL_FreeSurface(surface);
	}

	return ;
}

void	init_map(t_game *game)
{
	game->map = init_test_map();
	if (!game->map)
		exit_game(game, "Init map");

	precompute_mirrors(game->map);
	init_textures(game, game->map);

	return ;
}

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	load_settings(game);
	game->selected_language = 0;
	parse_languages(game, game->selected_language); //english par defaut
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
	free_languages(game);
    game->window->menus.main.has_init = 1;

	init_hud_cache(game);
	init_player(game, 500, 500, 0.0f, 1.0f);
	if (TTF_Init() < 0)
		exit_game(game, "TTF Init");

	game->frame_buffer = calloc(game->screenSize[0] * game->screenSize[1], sizeof(Uint32));
	game->rays = calloc(game->screenSize[0], sizeof(t_ray));
	game->fps = NULL;
	game->frame = SDL_CreateTexture(game->window->renderPTR,
								SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_STREAMING,
								game->screenSize[0],
								game->screenSize[1]);
	if (!game->frame_buffer || !game->rays || !game->frame)
		exit_game(game, "game malloc (frames)");
	init_map(game);
	game->window->menus.notif.notif_buf = NULL;
	game->window->menus.current = 1;
		
	return (game);
}
