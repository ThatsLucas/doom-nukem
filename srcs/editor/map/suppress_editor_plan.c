/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppress_editor_plan.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 11:46:47 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/05 12:22:33 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

static void	update_walls(t_map *map, int index)
{
	for (int i = 0; i < map->num_walls; ++i)
	{
		if (map->walls[i].v1 > index)
			map->walls[i].v1--;
		if (map->walls[i].v2 > index)
			map->walls[i].v2--;
	}

	return ;
}

void	suppress_vertice(t_game *game, float x, float y)
{
	t_vect2	*vertice;
	t_wall	*wall;
	int		index, i;

	vertice = get_clicked_vertice(game, x, y);
	if (!vertice)
		return ;

	index = vertice - game->editor->map->vertices;

	ft_memmove(vertice, vertice + 1, sizeof(t_vect2) * (game->editor->map->num_vertices - index - 1));
	game->editor->map->num_vertices--;

	i = 0;
	while (i < game->editor->map->num_walls)
	{
		wall = &game->editor->map->walls[i];
		if (index == wall->v1 || index == wall->v2)
			suppress_wall(game, i);
		else
			i++;
	}

	update_walls(game->editor->map, index);

	return ;
}

void	suppress_wall(t_game *game, int wall_indx)
{
	t_wall	*wall;

	if (wall_indx >= game->editor->map->num_walls || wall_indx < 0)
		return ;

	wall = &game->editor->map->walls[wall_indx];
	ft_memmove(wall, wall + 1, sizeof(t_wall) * (game->editor->map->num_walls - wall_indx - 1));
	game->editor->map->num_walls--;

	return ;
}
