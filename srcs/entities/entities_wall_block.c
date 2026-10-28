/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_wall_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:40:04 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/28 22:46:18 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"

/* Intersection du segment [p, p + r] avec le segment [a, b].
   Renvoie 1 si elles se coupent et met dans *t la position sur [p, p + r]. */
static int	segment_hit(t_vect2 p, t_vect2 r, t_vect2 a, t_vect2 b, float *t)
{
	t_vect2	s = {b.x - a.x, b.y - a.y};
	t_vect2	qp = {a.x - p.x, a.y - p.y};
	float	rs = r.x * s.y - r.y * s.x;
	float	u;

	if (fabsf(rs) < 1e-8f)
		return (0);
	*t = (qp.x * s.y - qp.y * s.x) / rs;
	u = (qp.x * r.y - qp.y * r.x) / rs;
	return (*t > 1e-4f && *t <= 1.0f && u >= 0.0f && u <= 1.0f);
}

/* Cherche le mur le plus proche coupé par la ligne de vue dans le secteur. */
static int	closest_wall_hit(t_map *map, int sector_id, int skip_wall,
				t_vect2 from, t_vect2 ray, float *best_t)
{
	t_sector	*sector = &map->sectors[sector_id];
	t_wall		*w;
	int			best = -1;
	float		t;

	*best_t = 2.0f;
	for (int i = 0; i < sector->num_walls; i++)
	{
		if (sector->walls[i] == skip_wall)
			continue ;
		w = &map->walls[sector->walls[i]];
		if (segment_hit(from, ray, map->vertices[w->v1], map->vertices[w->v2], &t)
			&& t < *best_t)
		{
			*best_t = t;
			best = sector->walls[i];
		}
	}
	return (best);
}

/* Vérifie que la ligne de vue passe dans l’ouverture du portail (sol / plafond). */
static int	portal_open_at(t_map *map, int cur, int next, t_vect2 hit, float z)
{
	float	floor = fmaxf(get_plane_z(map->sectors[cur].floor_plane, hit.x, hit.y),
				get_plane_z(map->sectors[next].floor_plane, hit.x, hit.y));
	float	ceil = fminf(get_plane_z(map->sectors[cur].ceil_plane, hit.x, hit.y),
				get_plane_z(map->sectors[next].ceil_plane, hit.x, hit.y));

	return (z > floor && z < ceil);
}

/* Vitre : portail dont la texture du milieu est dessinée en transparence. */
static int	is_glass(t_wall *w)
{
	return (w->tex_mid >= 0 && w->alpha > 0.0f && w->alpha < 1.0f);
}

/* Suit le segment de secteur en secteur a travers les portails.
   Renvoie 1 si un mur l’arrête,
   tr->t donne alors la fraction parcourue jusqu’a l’impact.
   Dans tous les cas tr->sector est le dernier secteur atteint. */
int	trace_segment(t_map *map, t_trace *tr)
{
	t_vect2	from = {tr->x, tr->y};
	t_vect2	ray = {tr->rx, tr->ry};
	t_wall	*w;
	int		came_from = -1;
	int		wall_id;
	int		next;
	float	t;

	for (int step = 0; step < MAX_SIGHT_STEPS; step++)
	{
		tr->t = 0.0f;
		if (tr->sector < 0 || tr->sector >= map->num_sectors)
			return (1);
		wall_id = closest_wall_hit(map, tr->sector, came_from, from, ray, &t);
		tr->t = 1.0f;
		if (wall_id < 0)
			return (0);
		tr->t = t;
		w = &map->walls[wall_id];
		if (w->next_sector == -1 || (tr->glass_blocks && is_glass(w)))
			return (1);
		next = wall_other_sector(map, wall_id, tr->sector);
		if (next < 0)
			return (1);
		if (!portal_open_at(map, tr->sector, next,
				(t_vect2){from.x + ray.x * t, from.y + ray.y * t}, tr->z + tr->rz * t))
			return (1);
		came_from = wall_id;
		tr->sector = next;
	}
	return (1);
}

/* Renvoie 1 si l'entite a une ligne de vue dégagée jusqu’au joueur.
   Les murs invisibles / transparents ne bloquent pas la vue, un mur plein si. */
int	check_wall_blocking(t_game *game, t_entity *e, t_target *target)
{
	float	z_from = e->z + ENTITY_EYE_HEIGHT;
	t_trace	tr = {.x = e->x, .y = e->y, .z = z_from,
		.rx = target->x - e->x, .ry = target->y - e->y, .rz = target->z - z_from,
		.sector = e->sector, .glass_blocks = 0};

	return (!trace_segment(game->map, &tr));
}

/* Renvoie 1 si l'entite peut aller en (nx, ny) sans sortir de son secteur. */
int	entity_can_move(t_game *game, t_entity *e, float nx, float ny)
{
	t_map		*map = game->map;
	t_sector	*sector;
	t_wall		*w;
	t_vect2		from = {e->x, e->y};
	t_vect2		ray = {nx - e->x, ny - e->y};
	float		len = sqrtf(ray.x * ray.x + ray.y * ray.y);
	float		t;

	if (e->sector < 0 || e->sector >= map->num_sectors)
		return (0);
	if (len < 1e-6f)
		return (1);
	ray.x += ray.x / len * ENTITY_WALL_MARGIN;
	ray.y += ray.y / len * ENTITY_WALL_MARGIN;
	sector = &map->sectors[e->sector];
	for (int i = 0; i < sector->num_walls; i++)
	{
		w = &map->walls[sector->walls[i]];
		if (segment_hit(from, ray, map->vertices[w->v1], map->vertices[w->v2], &t))
			return (0);
	}
	return (1);
}
