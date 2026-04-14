/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_mirror_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:06:56 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/14 13:09:21 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

/* trouve le mur qui est le portail de l'autre secteur */
int	find_mirror_wall(t_map *map, int wall_idx, int next_sector_id)
{
	t_wall		*portal	= &map->walls[wall_idx];
	t_sector	*next	= &map->sectors[next_sector_id];
	t_wall		*w;

	for (int i = 0; i < next->num_walls; i++)
	{
		w = &map->walls[next->walls[i]];
		if (w->v1 == portal->v2 && w->v2 == portal->v1)
			return (next->walls[i]);
	}
	return (-1);
}
