/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_smaller_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:03:33 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/14 13:09:45 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

/* Trouve le mur le plus proche touché par le rayon. */
void	find_smaller_ray(t_game *game, t_sector *sector, t_ray *ray, int skip_wall)
{
	t_wall		*w;
	t_vect2		a, b;

	for (int i = 0; i < sector->num_walls; i++)
	{
		if (sector->walls[i] == skip_wall)
			continue ;
		w = &game->map->walls[sector->walls[i]];
		a = game->map->vertices[w->v1];
		b = game->map->vertices[w->v2];
		max_inter_point(game->ply->pos, ray->dir, a, edge(a, b), ray, sector->walls[i]);
	}

	return ;
}
