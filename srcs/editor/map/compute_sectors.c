/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_sectors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:20:02 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 16:25:21 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Libère les secteurs déjà calculés. */
static void free_existing_sectors(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->num_sectors)
	{
		if (map->sectors[i].walls)
			free(map->sectors[i].walls);
		i++;
	}
	map->num_sectors = 0;
}

/* Ajoute un secteur à la carte. */
static int add_sector(t_map *map, int *loop, int count)
{
	t_sector	*s;
	t_sector	*new_arr;
	int			new_cap;

	if (map->num_sectors >= map->cap_sectors)
	{
		new_cap = (map->cap_sectors == 0) ? 4 : map->cap_sectors * 2;
		new_arr = realloc(map->sectors, new_cap * sizeof(t_sector));
		if (!new_arr)
			return (-1);
		map->sectors = new_arr;
		map->cap_sectors = new_cap;
	}
	s = &map->sectors[map->num_sectors];
	s->walls = calloc(count, sizeof(int));
	if (!s->walls)
		return (-1);
	memcpy(s->walls, loop, count * sizeof(int));
	s->num_walls = count;

	s->floor_plane		= (t_plane){0.0f, 0.0f, 1.0f, 0.0f};
	s->ceil_plane		= (t_plane){0.0f, 0.0f, 1.0f, -4.0f};
	s->floor_tex		= 0;
	s->ceil_tex			= 0;
	s->sky_tex			= -1;
	s->light_level		= 255;
	s->has_floor_arrow	= 0;
	s->has_ceil_arrow	= 0;
	s->isElevating		= 0;
	s->levelSize		= 0;
	s->direction		= 0;
	return (map->num_sectors++);
}

/* Traite la boucle des demi-arêtes d’un secteur. */
static void	process_he_loop(t_map *map, int start, int *visited, int *loop, int *wall_ids)
{
	int		count, i;
	float	area;

	count = trace_he_loop(map, start, loop);
	if (count >= 3)
	{
		i = 0;
		while (i < count) { visited[loop[i]] = 1; i++; }
		area = signed_area_he(map, loop, count);
		if (area > 0.0f)
		{
			i = 0;
			while (i < count) { wall_ids[i] = he_wall(loop[i]); i++; }
			add_sector(map, wall_ids, count);
		}
	}
	else
		visited[start] = 1;
}

/* Détecte les secteurs à partir des boucles de murs. */
void compute_sectors(t_map *map)
{
	int		*visited, *loop, *wall_ids;
	int		total;

	if (!map || map->num_walls == 0)
		return ;

	free_existing_sectors(map);
	total = 2 * map->num_walls;
	visited = calloc(total, sizeof(int));
	loop = calloc(total, sizeof(int));
	wall_ids = calloc(total, sizeof(int));

	if (visited && loop && wall_ids)
	{
		for (int start = 0; start < total; ++start)
		{
			if (!visited[start])
				process_he_loop(map, start, visited, loop, wall_ids);
		}
	}

	free(visited);
	free(loop);
	free(wall_ids);
	return ;
}
