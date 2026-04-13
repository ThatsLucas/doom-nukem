/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 16:25:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/13 22:44:13 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	init_textures(t_game *game, t_map *map)
{
	map->surface[0] = SDL_LoadBMP("assets/east.bmp");
	map->surface[1] = SDL_LoadBMP("assets/north.bmp");
	map->surface[2] = SDL_LoadBMP("assets/south.bmp");
	map->surface[3] = SDL_LoadBMP("assets/west.bmp");
	map->text_colors = calloc(4, sizeof(t_RGB *));
	for (int i = 0; i < 4; i++)
	{
		SDL_Surface *s = map->surface[i];
		if (!s)
			exit_game(game, "init_textures");
		SDL_Surface *converted = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ARGB8888, 0);
		map->text_colors[i] = calloc(s->w * s->h, sizeof(t_RGB));
		Uint32 *pixels = (Uint32 *)converted->pixels;
		for (int j = 0; j < converted->w * converted->h; j++)
		SDL_GetRGB(pixels[j], converted->format, &map->text_colors[i][j].r,
		&map->text_colors[i][j].g, &map->text_colors[i][j].b);
		SDL_FreeSurface(converted);
	}

	return ;
}

void	init_map(t_game *game)
{
	game->map = calloc(1, sizeof(t_map));
	if (!game->map)
		exit_game(game, "Init map");
	game->map->num_textures = 4;

	init_textures(game, game->map);

	return ;
}

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_bzero(game, sizeof(t_game));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS))
		exit_game(game, "SDL_INIT");
	get_screen_size(&game->screenSize[0], &game->screenSize[1]);
	game->window = create_window("Doom Nukem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game->screenSize[0], game->screenSize[1], SDL_WINDOW_OPENGL);
	if (!game->window)
		exit_game(game, "create_window");
	game->ply = malloc(sizeof(t_ply));
	game->frame_buffer = calloc(game->screenSize[0] * game->screenSize[1], sizeof(Uint32));
	game->rays = calloc(game->screenSize[0], sizeof(t_ray));
	game->fps = NULL;
	game->frame = SDL_CreateTexture(game->window->renderPTR,
								SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_STREAMING,
								game->screenSize[0],
								game->screenSize[1]);
	if (!game->ply || !game->frame_buffer || !game->rays || !game->frame)
		exit_game(game, "player malloc");
	ft_bzero(game->ply, sizeof(t_ply));
	init_map(game);
	return (game);
}
