/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_ai.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:40:04 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 11:40:04 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"
#include "GUI/HUD.h"

/* Renvoie l’écart entre deux angles, ramené dans [-π, π]. */
float	angle_diff(float a, float b)
{
	float diff = fmod(b - a + M_PI, 2 * M_PI) - M_PI;

	return (diff);
}

/* Vérifie si l’entité voit le joueur. */
int	check_vision(t_game *game, t_entity *e, t_ply *p)
{
	float	dx = p->pos.x - e->x;
	float	dy = p->pos.y - e->y;
	float	distance = sqrtf(dx * dx + dy * dy);

	if (distance > e->vision_range)
		return (0);
	if (distance < 0.001f)
		return (1);

	dx /= distance;
	dy /= distance;

	float	dot = dx * e->dir_x + dy * e->dir_y;
	float	limit = cos((e->vision_angle * M_PI / 180.0f) * 0.5f);

	if (dot < limit)
		return (0);

	return (check_wall_blocking(game, e, p));
}

/* Rapproche l’entité du joueur sans la faire sortir de son secteur. */
void	move_to_ply(t_game *game, t_entity *e, t_ply *p, float dt)
{
	t_vect2	dir;
	float	nx;
	float	ny;

	dir.x = p->pos.x - e->x;
	dir.y = p->pos.y - e->y;

	float	dist = sqrtf(dir.x * dir.x + dir.y * dir.y);

	if (dist < 0.001f || dist < e->attack_range * 0.7f)
		return ;

	dir.x /= dist;
	dir.y /= dist;

	nx = e->x + dir.x * e->speed * dt;
	ny = e->y + dir.y * e->speed * dt;

	/* glisse le long des murs au lieu de les traverser */
	if (entity_can_move(game, e, nx, ny))
	{
		e->x = nx;
		e->y = ny;
	}
	else if (entity_can_move(game, e, nx, e->y))
		e->x = nx;
	else if (entity_can_move(game, e, e->x, ny))
		e->y = ny;
}

/* Inflige des dégâts aléatoires au joueur selon la cadence de tir. */
void	attack_ply(t_ply *p, t_entity *e)
{
	long long current = get_time_ms();

	if (e->last_shot_time == 0)
		e->last_shot_time = current;

	if ((current - e->last_shot_time) / 10 < e->fire_rate)
		return ;

	e->last_shot_time = current;

	srand((int)get_time_ms());
	int	damage = e->damage;
	if (e->damage > 4)
		damage = rand() % (e->damage - 4 + 1) + 4;
	if (rand() % 10 == 0)
		damage = 0;
	p->hp -= damage;
}
