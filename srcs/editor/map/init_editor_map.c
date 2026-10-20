/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 09:59:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:17:40 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Crée une texture à partir d’une couleur. */
static t_RGB	*create_texture_color(t_game *game, SDL_Surface *s, int w, int h)
{
	t_RGB	*res;
	Uint32	*pixels, pixel;

	res = calloc(w * h, sizeof(t_RGB));
	if (!res)
		exit_game(game, "Can't init texture colors");

	pixels = (Uint32 *)s->pixels;
	for (int y = 0; y < h; ++y)
	{
		for(int x = 0; x < w; ++x)
		{
			pixel = pixels[y * (s->pitch / 4) + x];
			SDL_GetRGBA(pixel, s->format, &res[w * y + x].r, &res[w * y + x].g,
				&res[w * y + x].b, &res[w * y + x].alphaValue);
		}
	}

	return (res);
}

/* Lit les couleurs des pixels d’une texture. */
static t_RGB	*read_texture_colors(t_game *game, SDL_Texture *texture, int width, int height)
{
	SDL_Renderer	*renderer = game->window->renderPTR;
	SDL_Texture		*target;
	SDL_Surface		*surface;
	t_RGB			*colors;

	target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetRenderTarget(renderer, target);
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	surface = SDL_CreateRGBSurface(0, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA8888, surface->pixels, surface->pitch);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_DestroyTexture(target);
	colors = create_texture_color(game, surface, width, height);

	SDL_FreeSurface(surface);
	return (colors);
}

/* Initialise les textures de la carte. */
static void	init_map_textures(t_game *game)
{
	t_map			*map = game->editor->map;
	int				width, height, i;
	SDL_Texture		*texture;

	while (map->cap_textures < game->editor->textures->num_textures)
		map_realloc(game, (void **)&map->textures, &map->cap_textures, sizeof(t_tex));

	for (i = 0; i < game->editor->textures->num_textures; ++i)
	{
		texture = game->editor->textures->textures[i];
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);
		map->textures[i].h = height;
		map->textures[i].w = width;
		map->textures[i].colors = read_texture_colors(game, texture, width, height);
	}

	ft_printf("Editor: Map texture initialized (%d)\n", i);
	map->num_textures = i;

	return ;
}

/* Initialise la carte de l’éditeur. */
void	init_editor_map(t_game *game)
{
	t_map	*map = NULL;

	game->editor->map = calloc(1, sizeof(t_map));
	if (!game->editor->map)
		exit_game(game, "editor: cant calloc map");

	map = game->editor->map;

	map->vertices = calloc(16, sizeof(t_vect2));
	map->cap_vertices = 16;

	map->sectors = calloc(4, sizeof(t_sector));
	map->cap_sectors = 4;

	map->walls = calloc(8, sizeof(t_wall));
	map->cap_walls = 8;

	map->textures = calloc(8, sizeof(t_tex));
	map->cap_textures = 8;

	map->decals = calloc(8, sizeof(t_decal));
	map->cap_decals = 8;

	map->entities = calloc(8, sizeof(t_map_ent));
	map->cap_entities = 8;

	if (!map->vertices || !map->sectors || !map->walls || !map->textures || !map->entities || ! map->decals)
		exit_game(game, "editor: init_editor_map calloc failed");

	init_map_textures(game);

	return ;
}
