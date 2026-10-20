/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_sector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:46:32 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/22 16:06:03 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Raycasting/Types.h"
#include "Game.h"

/* Transfère le joueur vers le secteur voisin après le passage d’un portail. */
static void	update_by_crossing(t_game *game, t_vect2 oldpos)
{
	t_sector	*sec;
	t_wall		*w;
	t_vect2		a, b;
	float		side_old, side_new;
	int			cur, neigh;

	cur = game->ply->sector;
	sec = &game->map->sectors[cur];
	for (int i = 0; i < sec->num_walls; i++)
	{
		w = &game->map->walls[sec->walls[i]];
		if (w->next_sector == -1)
			continue ;
		a = game->map->vertices[w->v1];
		b = game->map->vertices[w->v2];
		side_old = (b.x - a.x) * (oldpos.y - a.y) - (b.y - a.y) * (oldpos.x - a.x);
		side_new = (b.x - a.x) * (game->ply->pos.y - a.y) - (b.y - a.y) * (game->ply->pos.x - a.x);
		if ((side_old > 0 && side_new <= 0) || (side_old <= 0 && side_new > 0))
		{
			neigh = wall_other_sector(game->map, sec->walls[i], cur);
			if (neigh >= 0)
				game->ply->sector = neigh;
			return ;
		}
	}
}

/* Met à jour le secteur dans lequel se trouve le joueur. */
void	update_player_sector(t_game *game, t_vect2 oldpos)
{
	int	found;

	found = find_sector_z(game->map, game->ply->pos, game->ply->z);
	if (found >= 0)
	{
		game->ply->sector = found;
		return ;
	}
	update_by_crossing(game, oldpos);
}
