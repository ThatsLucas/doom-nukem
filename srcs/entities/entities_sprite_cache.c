/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_sprite_cache.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 10:00:00 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/29 10:00:00 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/GUI.h"

/* Décode un PNG et le convertit en texture logicielle. */
static t_tex	*decode_sprite(t_game *game, char *path, int w, int h)
{
	t_png	png;
	t_tex	*tex;

	png.w = w;
	png.h = h;
	png.path = ft_strdup(path);
	if (!png.path)
		exit_game(game, "Failed to strdup sprite path");
	if (!process_png(&png))
		exit_game(game, "Failed to load sprite");
	tex = create_sprite(&png);
	if (!tex)
		exit_game(game, "Failed to create sprite");
	return (tex);
}

/* Agrandit le cache si besoin. */
static void	grow_cache(t_game *game, t_sprite_cache *cache)
{
	t_cached_sprite	*tmp;

	if (cache->count < cache->capacity)
		return ;
	cache->capacity += 16;
	tmp = realloc(cache->list, cache->capacity * sizeof(t_cached_sprite));
	if (!tmp)
		exit_game(game, "Failed to realloc sprite cache");
	cache->list = tmp;
}

/* Renvoie la texture du PNG, décodée une seule fois puis partagée. */
t_tex	*get_cached_sprite(t_game *game, char *path, int w, int h)
{
	t_sprite_cache	*cache = &game->entities.sprites;
	t_cached_sprite	*entry;

	for (int i = 0; i < cache->count; i++)
	{
		entry = &cache->list[i];
		if (entry->w == w && entry->h == h && !ft_strcmp(entry->path, path))
			return (entry->tex);
	}
	grow_cache(game, cache);
	entry = &cache->list[cache->count];
	entry->path = ft_strdup(path);
	if (!entry->path)
		exit_game(game, "Failed to strdup sprite path");
	entry->w = w;
	entry->h = h;
	entry->tex = decode_sprite(game, path, w, h);
	cache->count++;
	return (entry->tex);
}

/* Libère toutes les textures du cache. */
void	free_sprite_cache(t_sprite_cache *cache)
{
	for (int i = 0; i < cache->count; i++)
	{
		free(cache->list[i].path);
		free(cache->list[i].tex->colors);
		free(cache->list[i].tex);
	}
	free(cache->list);
	cache->list = NULL;
	cache->count = 0;
	cache->capacity = 0;
}
