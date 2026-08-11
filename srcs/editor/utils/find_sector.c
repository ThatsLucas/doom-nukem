/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:55:48 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:17:36 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

static int	shared_vertex(t_wall *a, t_wall *b)
{
	if (a->v1 == b->v1 || a->v1 == b->v2)
		return (a->v1);
	return (a->v2);
}

float	sector_area(t_map *map, t_sector *s)
{
	float	area;
	int		pivot;
	int		next;
	t_vect2	p;
	t_vect2	q;
	int		i;

	if (s->num_walls < 3)
		return (0.0f);
	area = 0.0f;
	/* sommet partagé entre le dernier et le premier mur = point de départ */
	pivot = shared_vertex(
		&map->walls[s->walls[s->num_walls - 1]],
		&map->walls[s->walls[0]]);
	i = 0;
	while (i < s->num_walls)
	{
		next = shared_vertex(
			&map->walls[s->walls[i]],
			&map->walls[s->walls[(i + 1) % s->num_walls]]);
		p = map->vertices[pivot];
		q = map->vertices[next];
		area += p.x * q.y - q.x * p.y;
		pivot = next;
		i++;
	}
	return (fabsf(area) * 0.5f);
}

static int	point_in_sector_z(t_map *map, t_sector *sector, t_vect2 p, float z)
{
	int		inside = 0;
	t_wall	*w;
	t_vect2	a;
	t_vect2	b;

	for (int i = 0; i < sector->num_walls; i++)
	{
		w = &map->walls[sector->walls[i]];
		a = map->vertices[w->v1];
		b = map->vertices[w->v2];
		/* l'arête traverse-t-elle la ligne horizontale du point ? */
		if ((a.y > p.y) != (b.y > p.y))
		{
			/* x de l'intersection de l'arête avec la ligne y = p.y */
			float x_cross = a.x + (p.y - a.y) / (b.y - a.y) * (b.x - a.x);
			if (p.x < x_cross)
				inside = !inside;
		}
	}

	if (inside && z + 0.001f >= get_plane_z(sector->floor_plane, p.x, p.y) && z < get_plane_z(sector->ceil_plane, p.x, p.y))
		return (1);
	return (0);
}

/*	Trouve l'index du sector dans lequel est le point ou -1	*/
int	find_sector_z(t_map *map, t_vect2 p, float z)
{
	int		best_sector = -1;
	float	sarea, best_area = FLT_MAX;

	for (int i = 0; i < map->num_sectors; i++)
	{
		if (point_in_sector_z(map, &map->sectors[i], p, z))
		{
			sarea = sector_area(map, &map->sectors[i]);
			if (sarea < best_area)
			{
				best_area = sarea;
				best_sector = i;
			}
		}
	}
	return (best_sector);
}

static int	point_in_sector(t_map *map, t_sector *sector, t_vect2 p)
{
	int		inside = 0;
	t_wall	*w;
	t_vect2	a;
	t_vect2	b;

	for (int i = 0; i < sector->num_walls; i++)
	{
		w = &map->walls[sector->walls[i]];
		a = map->vertices[w->v1];
		b = map->vertices[w->v2];
		/* l'arête traverse-t-elle la ligne horizontale du point ? */
		if ((a.y > p.y) != (b.y > p.y))
		{
			/* x de l'intersection de l'arête avec la ligne y = p.y */
			float x_cross = a.x + (p.y - a.y) / (b.y - a.y) * (b.x - a.x);
			if (p.x < x_cross)
				inside = !inside;
		}
	}
	return (inside);
}

/*	Trouve l'index du sector dans lequel est le point ou -1	*/
int	find_sector(t_map *map, t_vect2 p)
{
	int		best_sector = -1;
	float	sarea, best_area = FLT_MAX;

	for (int i = 0; i < map->num_sectors; i++)
	{
		if (point_in_sector(map, &map->sectors[i], p))
		{
			sarea = sector_area(map, &map->sectors[i]);
			if (sarea < best_area)
			{
				best_area = sarea;
				best_sector = i;
			}
		}
	}
	return (best_sector);
}

