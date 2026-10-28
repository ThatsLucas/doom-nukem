/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_projectile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 22:37:50 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/28 22:38:23 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"

/* Tire une roquette depuis les yeux du joueur, dans la direction du viseur. */
void	spawn_rocket(t_game *game)
{
	t_ply			*ply = game->ply;
	float			focal = game->screenSize[0] * 0.5f / tanf(game->settings.FOV * 0.5f);
	float			dz = ply->pitch / focal;
	float			len = sqrtf(ply->dir.x * ply->dir.x + ply->dir.y * ply->dir.y + dz * dz);
	t_projectile	*p;

	load_proj_assets(game);
	p = calloc(1, sizeof(t_projectile));
	if (!p)
		exit_game(game, "malloc error");
	p->state = PROJ_FLYING;
	p->x = ply->pos.x;
	p->y = ply->pos.y;
	p->z = ply->z - PROJ_SPAWN_DROP;
	p->dx = ply->dir.x / len;
	p->dy = ply->dir.y / len;
	p->dz = dz / len;
	p->sector = ply->sector;
	p->next = game->projectiles;
	game->projectiles = p;
}

/* Renvoie 1 si la roquette touche une entité vivante (PNJ compris). */
static int	hit_entity(t_game *game, t_projectile *p)
{
	t_entity	*e;
	float		dx;
	float		dy;

	for (int i = 0; i < game->entities.count; i++)
	{
		e = &game->entities.list[i];
		if (e->hitbox <= 0 || e->status == E_STATUS_DEAD)
			continue ;
		dx = e->x - p->x;
		dy = e->y - p->y;
		if (dx * dx + dy * dy <= PROJ_ENTITY_RADIUS * PROJ_ENTITY_RADIUS
			&& p->z >= e->z && p->z <= e->z + PROJ_HIT_HEIGHT)
			return (1);
	}
	return (0);
}

/* Dégâts de zone : les ennemis proches et visibles depuis l’impact prennent des degats qui baissent avec la distance. */
static void	explode(t_game *game, t_projectile *p)
{
	t_entity	*e;
	t_trace		tr;
	float		d;
	int			damage;

	p->state = PROJ_EXPLODING;
	for (int i = 0; i < game->entities.count; i++)
	{
		e = &game->entities.list[i];
		if ((e->type != ENTITY_ENEMY && e->type != ENTITY_BOSS) || e->status == E_STATUS_DEAD)
			continue ;
		tr = (t_trace){.x = p->x, .y = p->y, .z = p->z, .rx = e->x - p->x,
			.ry = e->y - p->y, .rz = e->z + 1.0f - p->z, .sector = p->sector, .glass_blocks = 1};
		d = sqrtf(tr.rx * tr.rx + tr.ry * tr.ry + tr.rz * tr.rz);
		if (d >= PROJ_SPLASH_RADIUS || trace_segment(game->map, &tr))
			continue ;
		damage = (int)(ROCKET_DAMAGE * (1.0f - d / PROJ_SPLASH_RADIUS));
		// client multi : c'est l'hote qui applique les degats et renvoie l'etat
		if (game->settings.multiplayer_enabled && !game->settings.is_host)
		{
			report_entity_hit(game, i, damage);
			continue ;
		}
		e->hp -= damage;
		if (e->hp <= 0)
		{
			e->status = E_STATUS_DEAD;
			e->hitbox = 0;
		}
	}
}

/* Avance la roquette et la fait exploser sur un mur, une vitre, le sol,
   le plafond, une entité ou au-delà de la distance max. */
static void	update_flying(t_game *game, t_projectile *p, float dt)
{
	float		step = PROJ_SPEED * dt;
	t_trace		tr = {.x = p->x, .y = p->y, .z = p->z, .rx = p->dx * step,
		.ry = p->dy * step, .rz = p->dz * step, .sector = p->sector, .glass_blocks = 1};
	t_sector	*sec;

	if (trace_segment(game->map, &tr))
		return (explode(game, p));
	p->x += tr.rx;
	p->y += tr.ry;
	p->z += tr.rz;
	p->sector = tr.sector;
	p->traveled += step;
	sec = &game->map->sectors[p->sector];
	if (p->z <= get_plane_z(sec->floor_plane, p->x, p->y)
		|| p->z >= get_plane_z(sec->ceil_plane, p->x, p->y)
		|| hit_entity(game, p) || p->traveled >= PROJ_MAX_DIST)
		explode(game, p);
}

/* Met à jour les roquettes et libere celles dont l’explosion est finie. */
void	update_projectiles(t_game *game)
{
	static Uint64	last = 0;
	float			dt = frame_delta(&last);
	t_projectile	**cur = &game->projectiles;
	t_projectile	*p;

	while (*cur)
	{
		p = *cur;
		if (p->state == PROJ_FLYING)
			update_flying(game, p, dt);
		else
		{
			p->expl_timer += dt;
			p->expl_frame = (int)(p->expl_timer / 0.1f); /* 0.1 s par image */
		}
		if (p->expl_frame >= 3)
		{
			*cur = p->next;
			free(p);
			continue ;
		}
		cur = &p->next;
	}
}
