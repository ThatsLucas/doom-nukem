/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_add_vertice.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:41:46 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/08 11:57:52 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

t_vect2	*get_clicked_vertice(t_game *game, float x, float y)
{
	t_map	*map = game->editor->map;
	t_vect2	pos = {.x = x, .y = y};

	for (int i = 0; i < map->num_vertices; ++i)
	{
		if (dist_vect(pos, map->vertices[i]) < CLICK_OFFSET)
			return (&map->vertices[i]);
	}

	return (NULL);
}

void	editor_add_vertice(t_game *game, float x, float y)
{
	t_map	*map = game->editor->map;
	t_vect2	*vertice;

	if (get_clicked_vertice(game, x, y))
		return ;

	if (map->num_vertices == map->cap_vertices)
		map_realloc(game, (void **)&map->vertices, &map->cap_vertices, sizeof(t_vect2));

	vertice = &map->vertices[map->num_vertices];
	vertice->x = x;
	vertice->y = y;
	map->num_vertices++;

	return ;
}
