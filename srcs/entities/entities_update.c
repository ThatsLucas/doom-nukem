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
static void	actions_base_on_state(t_entity *e, t_game *game, t_target *t, float dt)
{
	if (e->status == E_STATUS_CHASE)
		move_to_ply(game, e, t, dt);
	else if (e->status == E_STATUS_ATTACK)
	{
		if (t->net_index < 0)
			attack_ply(game->ply, e);
		else // joueur distant : le serveur lui transmettra les degats
			damage_remote_player(game, t->net_index, entity_attack_damage(e));
	}
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

/* Liste les joueurs vivants que les ennemis peuvent viser.
   L'hote voit aussi les joueurs distants recus du serveur. */
static int	collect_targets(t_game *game, t_target *targets)
{
	t_udp_connections	*c = &game->clientConnection;
	int					n = 0;

	if (game->ply->hp > 0)
		targets[n++] = (t_target){game->ply->pos.x, game->ply->pos.y,
			game->ply->z, game->ply->sector, -1};
	if (!game->settings.multiplayer_enabled || !game->settings.is_host)
		return (n);
	for (int i = 0; i < c->player_count && i < 4; i++)
	{
		if (i == c->selfIndex || c->player_hp[i] <= 0)
			continue ;
		t_vect2	pos = {c->players[i][0], c->players[i][1]};
		int		sector = find_sector_z(game->map, pos, c->players[i][2]);
		if (sector < 0)
			continue ;
		targets[n++] = (t_target){pos.x, pos.y,
			c->players[i][2] + EYES_HEIGTH, sector, i};
	}
	return (n);
}

/* Met à jour l’état et les actions d’un ennemi, en visant le joueur visible le plus proche. */
static void	update_enemy(t_entity *e, t_game *game, t_target *targets, int count, float dt)
{
	t_target	*best = NULL;
	float		best_dist = 0;
	float		dx;
	float		dy;
	float		distance;

	if (e->status == E_STATUS_DEAD)
		return ;
	for (int i = 0; i < count; i++)
	{
		dx = targets[i].x - e->x;
		dy = targets[i].y - e->y;
		distance = sqrtf(dx * dx + dy * dy);
		if ((!best || distance < best_dist) && check_vision(game, e, &targets[i]))
		{
			best = &targets[i];
			best_dist = distance;
		}
	}
	if (!best)
	{
		update_enemy_status(e, 0, 0, 0);
		return ;
	}
	if (best_dist > 0.001f)
	{
		e->dir_x = (best->x - e->x) / best_dist;
		e->dir_y = (best->y - e->y) / best_dist;
	}
	update_enemy_status(e, best_dist, 1, e->sector == best->sector);
	actions_base_on_state(e, game, best, dt);
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

	// client multi : l'hote simule les entites et nous envoie leur etat
	if (game->settings.multiplayer_enabled && !game->settings.is_host)
		return ;
	t_target	targets[5];
	int			count = collect_targets(game, targets);

	for (int i = 0; i < e->count; i++)
	{
		if (e->list[i].type == ENTITY_ENEMY || e->list[i].type == ENTITY_BOSS)
			update_enemy(&e->list[i], game, targets, count, dt);
	}
}
