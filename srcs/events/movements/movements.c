/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:21:43 by edurance          #+#    #+#             */
/*   Updated: 2026/10/20 16:30:13 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"

/* Gère les déplacements vers l’avant et l’arrière. */
static void medial_moves(t_ply *ply, t_game *game)
{
	float steps;
	float next_x;
	float next_y;
	int direction;

	if (ply->keys.w && ply->keys.s)
		return;
	steps = ply->physic.speed + ((ply->physic.is_running) ? 0.03f : 0.0f);
	if (ply->keys.w)
		direction = 1;
	if (ply->keys.s)
		direction = -1;
	next_x = ply->pos.x + ply->dir.x * steps * direction;
	next_y = ply->pos.y + ply->dir.y * steps * direction;
	if (next_x >= 0.0f && next_x <= game->map->mapSize.x && next_y >= 0.0f && next_y <= game->map->mapSize.y && !entities_collision(game, next_x, next_y) && !wall_collision(game, next_x, next_y))
	{
		ply->pos.x = next_x;
		ply->pos.y = next_y;
	}
}

/* Gère les déplacements latéraux. */
static void lateral_moves(t_ply *ply, t_game *game)
{
	float steps;
	float next_x;
	float next_y;
	float ax;
	float ay;

	if (ply->keys.a && ply->keys.d)
		return;
	steps = ply->physic.speed + ((ply->physic.is_running) ? 0.03f : 0.0f);
	ax = ply->dir.x * cosf((M_PI / 2) * -1) - ply->dir.y * sinf((M_PI / 2) * -1);
	ay = ply->dir.x * sinf((M_PI / 2) * -1) + ply->dir.y * cosf((M_PI / 2) * -1);
	if (ply->keys.a)
	{
		next_x = ply->pos.x + ax * steps;
		next_y = ply->pos.y + ay * steps;
	}
	if (ply->keys.d)
	{
		next_x = ply->pos.x - ax * steps;
		next_y = ply->pos.y - ay * steps;
	}
	if (next_x >= 0.0f && next_x <= game->map->mapSize.x && next_y >= 0.0f && next_y <= game->map->mapSize.y && !entities_collision(game, next_x, next_y) && !wall_collision(game, next_x, next_y))
	{
		ply->pos.x = next_x;
		ply->pos.y = next_y;
	}
}

/* Déplace le joueur puis met à jour sa hauteur et son secteur. */
void ply_movements(t_ply *ply, t_game *game)
{
	t_vect2 oldpos;
	oldpos = ply->pos;

	if (!game->map)
		return;

	if (ply->keys.space)
	{
		player_jump(game);
		activate_jetpack(game);
	}
	if (ply->keys.w || ply->keys.s)
		medial_moves(ply, game);
	if (ply->keys.a || ply->keys.d)
		lateral_moves(ply, game);
	update_player_sector(game, oldpos);
	ply->floor_height = get_plane_z(game->map->sectors[ply->sector].floor_plane,
									ply->pos.x, ply->pos.y);
	ply->ceiling_height = get_plane_z(game->map->sectors[ply->sector].ceil_plane,
									  ply->pos.x, ply->pos.y);
}
