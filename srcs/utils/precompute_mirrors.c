/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_mirrors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:57:08 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/16 16:59:40 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	precompute_mirrors(t_map *map)
{
	t_wall	*w;

	for (int i = 0; i < map->num_walls; i++)
	{
		w = &map->walls[i];
		if (w->next_sector >= 0)
			w->mirror = find_mirror_wall(map, i, w->next_sector);
		else
			w->mirror = -1;
	}
}
