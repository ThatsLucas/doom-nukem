/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_place_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:57:02 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/29 23:22:56 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/*	Placer un wall dans l'editor en cliquant	*/
void	editor_place_wall(t_game *game, int pixx, int pixy)
{
	t_vect2	click_pos;
	t_vect2	*existing;
	t_map	*map = game->editor->map;

	if (pixx > game->editor->plan.size.w)
		return ;

	click_pos = pixels_to_pos(game->editor, (float)pixx, (float)pixy);
	if (click_pos.x < 0 || click_pos.y < 0 || click_pos.x > game->mapSize[0] || click_pos.y > game->mapSize[1])
		return ;

	existing = get_clicked_vertice(game, click_pos.x, click_pos.y);

	if (game->editor->properties.draw_wall_active && existing)
	{
		if (existing - map->vertices != game->editor->properties.last_vertex)
		{
			editor_add_wall(game, game->editor->properties.last_vertex, existing - map->vertices);
			game->editor->properties.draw_wall_active = 0;
			compute_sectors(map);
		}
		return ;
	}
	else if (existing)
	{
		game->editor->properties.draw_wall_active = 1;
		game->editor->properties.last_vertex = existing - map->vertices;
		return ;
	}

	editor_add_vertice(game, click_pos.x, click_pos.y);
	if (game->editor->properties.draw_wall_active)
	{
		int new_vertex = map->num_vertices - 1;

		editor_add_wall(game, game->editor->properties.last_vertex, new_vertex);
		game->editor->properties.last_vertex = new_vertex;
	}
	else
	{
		game->editor->properties.draw_wall_active = 1;
		game->editor->properties.last_vertex = map->num_vertices - 1;
	}

	return ;
}
