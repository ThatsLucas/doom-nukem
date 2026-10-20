/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_place_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:57:02 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:17:38 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Click on an existing vertice: close the current wall or start a new one */
static void	click_existing_vertice(t_game *game, t_map *map, t_vect2 *existing)
{
	t_editor_properties	*props = &game->editor->properties;

	if (props->draw_wall_active)
	{
		if (existing - map->vertices != props->last_vertex)
		{
			editor_add_wall(game, props->last_vertex, existing - map->vertices);
			props->draw_wall_active = 0;
			compute_sectors(map);
		}
		return ;
	}
	props->draw_wall_active = 1;
	props->last_vertex = existing - map->vertices;
}

/* Click on an empty spot: add a vertice and continue the current wall */
static void	click_new_vertice(t_game *game, t_map *map, t_vect2 click_pos)
{
	t_editor_properties	*props = &game->editor->properties;

	editor_add_vertice(game, click_pos.x, click_pos.y);
	if (props->draw_wall_active)
	{
		int new_vertex = map->num_vertices - 1;

		editor_add_wall(game, props->last_vertex, new_vertex);
		props->last_vertex = new_vertex;
	}
	else
	{
		props->draw_wall_active = 1;
		props->last_vertex = map->num_vertices - 1;
	}
}

/*	Placer un wall dans l'editor en cliquant	*/
void	editor_place_wall(t_game *game, int pixx, int pixy, int button)
{
	t_vect2	click_pos;
	t_vect2	*existing;
	t_map	*map = game->editor->map;

	if (button == SDL_BUTTON_RIGHT)
	{
		game->editor->properties.draw_wall_active = 0;
		return ;
	}

	if (button == SDL_BUTTON_MIDDLE || pixx > game->editor->plan.size.w)
		return ;

	click_pos = pixels_to_pos(game->editor, (float)pixx, (float)pixy);
	if (click_pos.x < 0 || click_pos.y < 0 || click_pos.x > map->mapSize.x || click_pos.y > map->mapSize.y)
		return ;

	existing = get_clicked_vertice(game, click_pos.x, click_pos.y);
	if (existing)
		click_existing_vertice(game, map, existing);
	else
		click_new_vertice(game, map, click_pos);
}
