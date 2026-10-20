/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_assets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:03:09 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:03:09 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

int	load_textures(t_map *map, int fd)
{
	int		i;
	t_tex	*t;

	if (read_full(fd, &map->num_textures, sizeof(int)))
		return (-1);
	if (map->num_textures < 0 || map->num_textures > INT_MAX)
		return (-1);
	map->textures = ft_calloc(map->num_textures, sizeof(t_tex));
	if (!map->textures)
		return (-1);
	i = 0;
	while (i < map->num_textures)
	{
		t = &map->textures[i];
		if (read_full(fd, &t->w, sizeof(int))
			|| read_full(fd, &t->h, sizeof(int)))
			return (-1);
		if (t->w <= 0 || t->h <= 0 || t->w > INT_MAX || t->h > INT_MAX)
			return (-1);
		t->colors = ft_calloc((size_t)t->w * t->h, sizeof(t_RGB));
		if (!t->colors)
			return (-1);
		if (read_full(fd, t->colors, sizeof(t_RGB) * (size_t)t->w * t->h))
			return (-1);
		i++;
	}
	return (0);
}

static int	load_decal(t_decal *d, int fd)
{
	if (read_full(fd, &d->wall_idx, sizeof(int))
		|| read_full(fd, &d->u_offset, sizeof(float))
		|| read_full(fd, &d->width, sizeof(float))
		|| read_full(fd, &d->z_bottom, sizeof(float))
		|| read_full(fd, &d->height, sizeof(float))
		|| read_full(fd, &d->elev_sector, sizeof(int))
		|| read_full(fd, &d->sector_id, sizeof(int))
		|| read_full(fd, &d->need_key, sizeof(int))
		|| read_full(fd, &d->pos, sizeof(t_vect2))
		|| read_full(fd, &d->texture.w, sizeof(int))
		|| read_full(fd, &d->texture.h, sizeof(int)))
		return (-1);
	if (d->texture.w <= 0 || d->texture.h <= 0
		|| d->texture.w > INT_MAX || d->texture.h > INT_MAX)
		return (-1);
	d->texture.colors = ft_calloc((size_t)d->texture.w * d->texture.h, sizeof(t_RGB));
	if (!d->texture.colors)
		return (-1);
	if (read_full(fd, d->texture.colors,
			sizeof(t_RGB) * (size_t)d->texture.w * d->texture.h))
		return (-1);
	return (0);
}

int	load_spawn_and_decals(t_map *map, int fd)
{
	int	i;

	if (read_full(fd, &map->player_spawn, sizeof(t_vect2)))
		return (-1);
	if (read_full(fd, &map->player_dir, sizeof(t_vect2)))
		return (-1);
	if (read_full(fd, &map->num_decals, sizeof(int)))
		return (-1);
	if (map->num_decals < 0 || map->num_decals > INT_MAX)
		return (-1);
	map->decals = ft_calloc(map->num_decals, sizeof(t_decal));
	if (!map->decals)
		return (-1);
	i = 0;
	while (i < map->num_decals)
	{
		if (load_decal(&map->decals[i], fd))
			return (-1);
		i++;
	}
	return (0);
}

int	load_entities(t_map *map, int fd)
{
	int	i;
	int	r;

	r = read_full(fd, &map->num_entities, sizeof(int));
	if (r < 0)
	{
		map->num_entities = 0;
		map->entities = NULL;
		map->cap_entities = 0;
		return (0);
	}
	if (map->num_entities < 0 || map->num_entities > INT_MAX)
		return (-1);
	map->entities = ft_calloc(map->num_entities, sizeof(t_map_ent));
	if (!map->entities)
		return (-1);
	i = 0;
	while (i < map->num_entities)
	{
		if (read_full(fd, &map->entities[i].pos, sizeof(t_vect2))
			|| read_full(fd, &map->entities[i].ang, sizeof(t_vect2))
			|| read_full(fd, &map->entities[i].sector_id, sizeof(int))
			|| read_full(fd, &map->entities[i].id, sizeof(int))
			|| read_full(fd, &map->entities[i].type, sizeof(int)))
			return (-1);
		i++;
	}
	map->cap_entities = map->num_entities;
	return (0);
}
