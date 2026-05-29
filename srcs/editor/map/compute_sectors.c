/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_sectors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:20:02 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/25 13:33:12 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/*	Demi-arêtes (half-edges)
	Encodage : he = 2 * wall_idx + dir   (dir = 0 forward, 1 reverse)
*/

static int	he_wall(int he)			{ return he / 2; }
static int	he_is_forward(int he)	{ return (he % 2) == 0; }

static int	he_start(t_map *map, int he)
{
	t_wall *w = &map->walls[he / 2];
	return he_is_forward(he) ? w->v1 : w->v2;
}

static int	he_end(t_map *map, int he)
{
	t_wall *w = &map->walls[he / 2];
	return he_is_forward(he) ? w->v2 : w->v1;
}

/*
	Angle "sortant" d'une demi-arête depuis son vertex de départ
*/
static float	he_out_angle(t_map *map, int he)
{
	t_vect2 a = map->vertices[he_start(map, he)];
	t_vect2 b = map->vertices[he_end(map, he)];
	return atan2f(b.y - a.y, b.x - a.x);
}

/*
	On vient d'arriver par current_he. On cherche la demi-arête
	sortante qui correspond au "prochain bord de la même face".

	On prend le voisin dont l'angle est le PLUS PROCHE de back_angle
	en tournant dans le sens CW math (= CCW visuel en coords écran)

	On garde le plus petit delta.
*/
static int	next_he_in_loop(t_map *map, int current_he, int pivot)
{
	int		i, total, best;
	float	best_delta, back_angle, out_angle, delta;

	t_vect2 p = map->vertices[pivot];
	t_vect2 prev = map->vertices[he_start(map, current_he)];
	back_angle = atan2f(prev.y - p.y, prev.x - p.x);	// Angle retour : depuis pivot vers d'où on vient

	total = 2 * map->num_walls;
	best = -1;
	best_delta = 0.0f;
	i = 0;
	while (i < total)
	{
		if (i != current_he && he_start(map, i) == pivot)
		{
			out_angle = he_out_angle(map, i);
			delta = back_angle - out_angle;
			while (delta <= 0.0f)
				delta += 2.0f * M_PI;
			if (best == -1 || delta < best_delta)
			{
				best = i;
				best_delta = delta;
			}
		}
		i++;
	}
	return (best);
}

static int trace_he_loop(t_map *map, int start_he, int *loop_out)
{
	int origin_v, pivot, current, next, count, max_steps;

	origin_v = he_start(map, start_he);
	current = start_he;
	count = 0;
	max_steps = 2 * map->num_walls;
	while (count < max_steps)
	{
		loop_out[count++] = current;
		pivot = he_end(map, current);
		if (pivot == origin_v)
			return (count);
		next = next_he_in_loop(map, current, pivot);
		if (next == -1)
			return (-1);
		current = next;
	}
	return (-1);
}

/*
	Aire signée d'une boucle de demi-arêtes
*/
static float signed_area_he(t_map *map, int *loop, int count)
{
	int		i;
	float	area;
	t_vect2	a, b;

	area = 0.0f;
	i = 0;
	while (i < count)
	{
		a = map->vertices[he_start(map, loop[i])];
		b = map->vertices[he_end(map, loop[i])];
		area += (a.x * b.y) - (b.x * a.y);
		i++;
	}
	return (area * 0.5f);
}

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

	s->floor_plane	= (t_plane){0.0f, 0.0f, 1.0f, 0.0f};
	s->ceil_plane	= (t_plane){0.0f, 0.0f, 1.0f, 4.0f};
	s->floor_tex	= -1;
	s->ceil_tex		= -1;
	s->sky_tex		= -1;
	s->light_level	= 200;
	return (map->num_sectors++);
}

void compute_sectors(t_map *map)
{
	int		*visited, *loop, *wall_ids;
	int		total, count, i;
	float	area;

	if (!map || map->num_walls == 0)
		return ;

	free_existing_sectors(map);
	total = 2 * map->num_walls;
	visited = calloc(total, sizeof(int));
	loop = calloc(total, sizeof(int));
	wall_ids = calloc(total, sizeof(int));

	if (!visited || !loop || !wall_ids)
	{
		free(visited);
		free(loop);
		free(wall_ids);
		return ;
	}

	for (int start = 0; start < total; ++start)
	{
		if (!visited[start])
		{
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
	}

	free(visited);
	free(loop);
	free(wall_ids);
	return ;
}
