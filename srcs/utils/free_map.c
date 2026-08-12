/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 16:52:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:21:37 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Types.h"
#include "Game.h"

void free_map(t_map *map)
{
	if (!map)
		return;
	for (int i = 0; i < map->num_sectors; i++)
		free(map->sectors[i].walls);
	for (int y = 0; y < map->num_textures; y++)
		free(map->textures[y].colors);
	for (int i = 0; i < map->num_decals; i++)
		free(map->decals[i].texture.colors);
	free(map->sectors);
	free(map->walls);
	free(map->vertices);
	free(map->textures);
	free(map->decals);
	free(map->entities);
	free(map);

	return ;
}
