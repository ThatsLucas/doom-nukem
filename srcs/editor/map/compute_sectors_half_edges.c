/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_sectors_half_edges.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:04:12 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 16:25:12 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/*	Demi-arêtes (half-edges)
	Encodage : he = 2 * wall_idx + dir   (dir = 0 forward, 1 reverse)
*/

/* Renvoie l’indice du mur de la demi-arête. */
int		he_wall(int he)			{ return he / 2; }
/* Vérifie si la demi-arête est orientée vers l’avant. */
static int	he_is_forward(int he)	{ return (he % 2) == 0; }

/* Récupère le sommet de départ de la demi-arête. */
static int	he_start(t_map *map, int he)
{
	t_wall *w = &map->walls[he / 2];
	return he_is_forward(he) ? w->v1 : w->v2;
}

/* Récupère le sommet d’arrivée de la demi-arête. */
static int	he_end(t_map *map, int he)
{
	t_wall *w = &map->walls[he / 2];
	return he_is_forward(he) ? w->v2 : w->v1;
}

/* Calcule l’angle sortant de la demi-arête. */
static float	he_out_angle(t_map *map, int he)
{
	t_vect2 a = map->vertices[he_start(map, he)];
	t_vect2 b = map->vertices[he_end(map, he)];
	return atan2f(b.y - a.y, b.x - a.x);
}

/* Récupère la demi-arête suivante dans la boucle. */
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

/* Suit une boucle fermée de demi-arêtes et renvoie sa taille. */
int	trace_he_loop(t_map *map, int start_he, int *loop_out)
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

/* Calcule l’aire signée d’une boucle de demi-arêtes. */
float	signed_area_he(t_map *map, int *loop, int count)
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
