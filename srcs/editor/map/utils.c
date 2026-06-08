/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 09:59:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/08 11:58:16 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"


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

static void	init_map_textures(t_game *game)
{
	t_map			*map = game->editor->map;
	int				width, height;
	SDL_Texture		*texture, *target;
	SDL_Surface		*surface;
	SDL_Renderer	*renderer = game->window->renderPTR;

	while (map->cap_textures < game->editor->textures->num_textures)
		map_realloc(game, (void **)&map->textures, &map->cap_textures, sizeof(t_tex));

	for (int i = 0; i < game->editor->textures->num_textures; ++i)
	{
		texture = game->editor->textures->textures[i];
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);
		map->textures[i].h = height;
		map->textures[i].w = width;
		target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
		SDL_SetRenderTarget(renderer, target);
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		surface = SDL_CreateRGBSurface(0, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
		SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA8888, surface->pixels, surface->pitch);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_DestroyTexture(target);
		map->textures[i].colors = create_texture_color(game, surface, width, height);

		SDL_FreeSurface(surface);
	}

	ft_printf("Editor: Map texture initialized\n");

	return ;
}

/*	Initialisation de la map de l'Editor	*/
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

	if (!map->vertices || !map->sectors || !map->walls || !map->textures)
		exit_game(game, "editor: init_editor_map calloc failed");

	init_map_textures(game);

	return ;
}

/*	Réallouer le tableau dynamique de la map	*/
void	map_realloc(t_game *game, void **pointer, int *cap, unsigned int sizeofone)
{
	int		new_cap;
	void	*new_ptr;

	new_cap = *cap * 2;
	new_ptr = realloc(*pointer, new_cap * sizeofone);

	if (!new_ptr)
		exit_game(game, "map_realloc failed");

	*pointer = new_ptr;
	*cap = new_cap;

	return ;
}

int	get_wall_index(t_map *map, float x, float y)
{
	t_wall	*wall;
	t_vect2	pos;

	pos.x = x;
	pos.y = y;

	for (int i = 0; i < map->num_walls; ++i)
	{
		wall = &map->walls[i];
		if (point_on_segment(pos, map->vertices[wall->v1], map->vertices[wall->v2], 0.1f))
			return (i) ;
	}

	return (-1);
}
