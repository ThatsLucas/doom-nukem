/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 16:25:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/22 14:28:21 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

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
	int		x, y;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_bzero(game, sizeof(t_game));

	if (TTF_Init() < 0)
		exit_game(game, "TTF Init");

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS))
		exit_game(game, "SDL_INIT");
	get_screen_size(&x, &y);
	game->window = create_window("Doom Nukem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_OPENGL);
	if (!game->window)
		exit_game(game, "create_window");
	game->window->w = x;
	game->window->h = y;
	game->ply = malloc(sizeof(t_ply));
	game->frame_buffer = calloc(game->window->w * game->window->h, sizeof(Uint32));
	game->rays = calloc(game->window->w, sizeof(t_ray));
	game->fps = NULL;
	game->frame = SDL_CreateTexture(game->window->renderPTR,
								SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_STREAMING,
								game->window->w,
								game->window->h);
	if (!game->ply || !game->frame_buffer || !game->rays || !game->frame)
		exit_game(game, "player malloc");
	ft_bzero(game->ply, sizeof(t_ply));
	init_map(game);
	game->window->PopupPtr.notif_buf = NULL;
	return (game);
}
