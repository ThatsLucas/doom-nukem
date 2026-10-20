/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_geometry.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:03:09 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:03:09 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Charge les données d’un mur. */
static int	load_one_wall(t_wall *w, int fd)
{
	if (read_full(fd, &w->v1, sizeof(int))
		|| read_full(fd, &w->v2, sizeof(int))
		|| read_full(fd, &w->next_sector, sizeof(int))
		|| read_full(fd, &w->length, sizeof(float))
		|| read_full(fd, &w->mirror, sizeof(int))
		|| read_full(fd, &w->tex_mid, sizeof(int))
		|| read_full(fd, &w->tex_upper, sizeof(int))
		|| read_full(fd, &w->tex_lower, sizeof(int))
		|| read_full(fd, &w->alpha, sizeof(float)))
		return (-1);
	w->sector_front = -1;
	w->sector_back = -1;
	return (0);
}

/* Charge les sommets et les murs. */
int	load_vertices_walls(t_map *map, int fd)
{
	int	i;

	if (read_full(fd, &map->num_vertices, sizeof(int)))
		return (-1);
	if (map->num_vertices < 0 || map->num_vertices > INT_MAX)
		return (-1);
	map->vertices = ft_calloc(map->num_vertices, sizeof(t_vect2));
	if (!map->vertices)
		return (-1);
	if (read_full(fd, map->vertices, sizeof(t_vect2) * map->num_vertices))
		return (-1);
	if (read_full(fd, &map->num_walls, sizeof(int)))
		return (-1);
	if (map->num_walls < 0 || map->num_walls > INT_MAX)
		return (-1);
	map->walls = ft_calloc(map->num_walls, sizeof(t_wall));
	if (!map->walls)
		return (-1);
	i = 0;
	while (i < map->num_walls)
	{
		if (load_one_wall(&map->walls[i], fd))
			return (-1);
		i++;
	}
	return (0);
}

/* Charge les données d’un secteur. */
static int	load_one_sector(t_sector *s, int fd)
{
	if (read_full(fd, &s->num_walls, sizeof(int)))
		return (-1);
	if (s->num_walls < 0 || s->num_walls > INT_MAX)
		return (-1);
	s->walls = ft_calloc(s->num_walls, sizeof(int));
	if (!s->walls)
		return (-1);
	if (read_full(fd, s->walls, sizeof(int) * s->num_walls))
		return (-1);
	if (read_full(fd, &s->floor_plane, sizeof(t_plane))
		|| read_full(fd, &s->ceil_plane, sizeof(t_plane))
		|| read_full(fd, &s->floor_tex, sizeof(int))
		|| read_full(fd, &s->ceil_tex, sizeof(int))
		|| read_full(fd, &s->sky_tex, sizeof(int))
		|| read_full(fd, &s->light_level, sizeof(int)))
		return (-1);
	if (read_full(fd, &s->floor_arrow_base, sizeof(t_vect2))
		|| read_full(fd, &s->floor_arrow_tip, sizeof(t_vect2))
		|| read_full(fd, &s->ceil_arrow_base, sizeof(t_vect2))
		|| read_full(fd, &s->ceil_arrow_tip, sizeof(t_vect2))
		|| read_full(fd, &s->has_floor_arrow, sizeof(int))
		|| read_full(fd, &s->has_ceil_arrow, sizeof(int)))
		return (-1);
	return (0);
}

/* Charge les secteurs. */
int	load_sectors(t_map *map, int fd)
{
	int	i;

	if (read_full(fd, &map->num_sectors, sizeof(int)))
		return (-1);
	if (map->num_sectors < 0 || map->num_sectors > INT_MAX)
		return (-1);
	map->sectors = ft_calloc(map->num_sectors, sizeof(t_sector));
	if (!map->sectors)
		return (-1);
	i = 0;
	while (i < map->num_sectors)
	{
		if (load_one_sector(&map->sectors[i], fd))
			return (-1);
		i++;
	}
	return (0);
}

/* Charge les ascenseurs. */
int	load_elevators(t_map *map, int fd)
{
	int	direction;
	int	level_size;

	for (int i = 0; i < map->num_sectors; ++i)
	{
		if (read_full(fd, &direction, sizeof(int))
			|| read_full(fd, &level_size, sizeof(int)))
			return (-1);
		map->sectors[i].direction = direction;
		map->sectors[i].levelSize = level_size;
	}
	return (0);
}
