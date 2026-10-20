/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_next_sectors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/24 15:53:06 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* cherche un autre secteur qui référence aussi le mur w */
static int	find_other_sector(t_map *map, int w, int owner_sector)
{
	int	si;
	int	wi;

	si = 0;
	while (si < map->num_sectors)
	{
		if (si != owner_sector)
		{
			wi = 0;
			while (wi < map->sectors[si].num_walls)
			{
				if (map->sectors[si].walls[wi] == w)
					return (si);
				wi++;
			}
		}
		si++;
	}
	return (-1);
}

static void	reset_wall_links(t_map *map)
{
	int	wi;

	wi = 0;
	while (wi < map->num_walls)
	{
		map->walls[wi].next_sector = -1;
		map->walls[wi].mirror = -1;
		map->walls[wi].sector_front = -1;
		map->walls[wi].sector_back = -1;
		wi++;
	}
}

/* Link the wall w (owned by sector si) to its front/back and next sector */
static void	link_wall(t_map *map, int w, int si)
{
	int	other;

	if (map->walls[w].sector_front == -1)
		map->walls[w].sector_front = si;
	else if (map->walls[w].sector_back == -1
		&& map->walls[w].sector_front != si)
		map->walls[w].sector_back = si;
	if (map->walls[w].next_sector == -1)
	{
		other = find_other_sector(map, w, si);
		if (other >= 0)
		{
			map->walls[w].next_sector = other;
			map->walls[w].mirror = w;
		}
	}
}

void	precompute_next_sectors(t_map *map)
{
	int	si;
	int	wi;
	int	w;

	if (!map || map->num_walls == 0 || map->num_sectors == 0)
		return ;
	reset_wall_links(map);
	si = 0;
	while (si < map->num_sectors)
	{
		wi = 0;
		while (wi < map->sectors[si].num_walls)
		{
			w = map->sectors[si].walls[wi];
			if (w >= 0 && w < map->num_walls)
				link_wall(map, w, si);
			wi++;
		}
		si++;
	}
}
