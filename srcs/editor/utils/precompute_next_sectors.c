/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_next_sectors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

void	precompute_next_sectors(t_map *map)
{
	t_sector	*sa;
	t_sector	*sb;
	int			wa;
	int			wb;

	for (int i = 0; i < map->num_walls; i++)
		map->walls[i].next_sector = -1;
	for (int si = 0; si < map->num_sectors; si++)
	{
		sa = &map->sectors[si];
		for (int wi = 0; wi < sa->num_walls; wi++)
		{
			wa = sa->walls[wi];
			for (int sj = si + 1; sj < map->num_sectors; sj++)
			{
				sb = &map->sectors[sj];
				for (int wj = 0; wj < sb->num_walls; wj++)
				{
					wb = sb->walls[wj];
					if (map->walls[wa].v1 == map->walls[wb].v2
						&& map->walls[wa].v2 == map->walls[wb].v1)
					{
						map->walls[wa].next_sector = sj;
						map->walls[wb].next_sector = si;
					}
				}
			}
		}
	}
}
