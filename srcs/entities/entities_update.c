/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:17:15 by edurance          #+#    #+#             */
/*   Updated: 2026/08/11 14:19:15 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"
#include "GUI/HUD.h"

/* Applique les actions correspondant à l’état de l’entité. */
static void	actions_base_on_state(t_entity *e, t_game *game, float dt)
{
	if (e->status == E_STATUS_CHASE)
		move_to_ply(game, e, game->ply, dt);
	else if (e->status == E_STATUS_ATTACK)
		attack_ply(game->ply, e);
}

/* Met à jour l’état de l’ennemi.
   Même secteur : il poursuit puis tire.
   Autre secteur (vu à travers un portail / mur invisible) : il tire sans bouger. */
static void	update_enemy_status(t_entity *e, float distance, int see_player, int same_sector)
{
	if (e->status == E_STATUS_DEAD)
		return ;
	if (!see_player)
		e->status = E_STATUS_IDLE;
	else if (distance <= e->attack_range)
		e->status = E_STATUS_ATTACK;
	else if (same_sector)
		e->status = E_STATUS_CHASE;
	else
		e->status = E_STATUS_ATTACK;
}

/* Met à jour l’état et les actions d’un ennemi. */
static void	update_enemy(t_entity *e, t_game *game, float dt)
{
	t_ply	*p = game->ply;
	float	dx = p->pos.x - e->x;
	float	dy = p->pos.y - e->y;
	float	distance = sqrtf(dx * dx + dy * dy);
	int		see_player;

	if (e->status == E_STATUS_DEAD)
		return ;
	see_player = check_vision(game, e, p);
	if (see_player && distance > 0.001f)
	{
		e->dir_x = dx / distance;
		e->dir_y = dy / distance;
	}
	update_enemy_status(e, distance, see_player, e->sector == p->sector);
	actions_base_on_state(e, game, dt);
}

/* Met à jour toutes les entités. */
void	update_entities(t_game *game, t_entities *e)
{
	static long long	last_time = 0;
	long long			current = get_time_ms();

	if (last_time == 0)
		last_time = current;

	float dt = (current - last_time) / 1000.0f;
	if (dt > 0.1f)
		dt = 0.1f;

	last_time = current;

	for (int i = 0; i < e->count; i++)
	{
		if (e->list[i].type == ENTITY_ENEMY || e->list[i].type == ENTITY_BOSS)
			update_enemy(&e->list[i], game, dt);
	}
}
