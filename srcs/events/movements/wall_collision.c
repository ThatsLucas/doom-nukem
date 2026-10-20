/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 12:00:00 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 16:30:32 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"

/* Détermine de quel côté du segment se trouve le point. */
static float cross_side(t_vect2 a, t_vect2 b, t_vect2 p)
{
	return ((b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x));
}

/* Vérifie si le déplacement traverse le mur. */
static int segments_cross(t_vect2 p1, t_vect2 p2, t_vect2 a, t_vect2 b)
{
	float d1 = cross_side(a, b, p1);
	float d2 = cross_side(a, b, p2);
	float d3 = cross_side(p1, p2, a);
	float d4 = cross_side(p1, p2, b);

	return (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0))
		&& ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)));
}

/* Calcule la hauteur libre nécessaire au passage du joueur. */
static float needed_headroom(t_ply *ply)
{
	if (ply->physic.is_crouching)
		return (EYES_HEIGTH / 2 + HEAD_MARGIN);
	return (EYES_HEIGTH + HEAD_MARGIN);
}

/* Vérifie si la marche ou le plafond du portail bloque le joueur. */
static int portal_is_blocked(t_game *game, int neigh, t_vect2 next)
{
	t_ply	*ply = game->ply;
	float	feet_z;
	float	floor;
	float	ceil;

	feet_z = ply->z - EYES_HEIGTH;
	if (ply->physic.is_on_ground)
		feet_z = ply->floor_height;
	floor = get_plane_z(game->map->sectors[neigh].floor_plane, next.x, next.y);
	ceil = get_plane_z(game->map->sectors[neigh].ceil_plane, next.x, next.y);
	if (floor - feet_z > STEP_HEIGHT)
		return (1);
	if (ceil - floor < needed_headroom(ply))
		return (1);
	if (ceil - feet_z < needed_headroom(ply))
		return (1);
	return (0);
}

/* Renvoie 1 si le déplacement traverse un mur ou un portail bloquant. */
int wall_collision(t_game *game, float next_x, float next_y)
{
	t_sector	*sec;
	t_wall		*w;
	t_vect2		next;
	int			neigh;

	next.x = next_x;
	next.y = next_y;
	sec = &game->map->sectors[game->ply->sector];
	for (int i = 0; i < sec->num_walls; i++)
	{
		w = &game->map->walls[sec->walls[i]];
		if (!segments_cross(game->ply->pos, next,
				game->map->vertices[w->v1], game->map->vertices[w->v2]))
			continue ;
		if (w->next_sector == -1)
			return (1);
		neigh = wall_other_sector(game->map, sec->walls[i], game->ply->sector);
		if (neigh < 0 || portal_is_blocked(game, neigh, next))
			return (1);
	}
	return (0);
}
