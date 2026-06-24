/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_sector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:46:32 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/16 17:54:44 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Raycasting/Types.h"
#include "Game.h"

/* Calcule si le joueur a change de sector et mets a jour la structure */
void	update_player_sector(t_game *game, t_vect2 oldpos)
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
