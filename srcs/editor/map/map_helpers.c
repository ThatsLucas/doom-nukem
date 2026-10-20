/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:04:28 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:04:28 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/*	Réallouer le tableau dynamique de la map	*/
void	map_realloc(t_game *game, void **pointer, int *cap, unsigned int sizeofone)
{
	int		new_cap;
	void	*new_ptr;

	if (*cap)
		new_cap = *cap * 2;
	else
		new_cap = 8;
	new_ptr = realloc(*pointer, new_cap * sizeofone);

	if (!new_ptr)
		exit_game(game, "map_realloc failed");

	*pointer = new_ptr;
	*cap = new_cap;

	return ;
}

int	get_wall_index(t_map *map, float x, float y)
{
	t_wall	*wall;
	t_vect2	pos;

	pos.x = x;
	pos.y = y;

	for (int i = 0; i < map->num_walls; ++i)
	{
		wall = &map->walls[i];
		if (point_on_segment(pos, map->vertices[wall->v1], map->vertices[wall->v2], 0.1f))
			return (i) ;
	}

	return (-1);
}
