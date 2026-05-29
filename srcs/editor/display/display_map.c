/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 11:06:23 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/29 18:07:33 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

void	display_editor_map(t_game *game)
{
	t_map	*map = game->editor->map;
	t_RGB	color = {0, 10, 59, 255};
	t_vect2	pos, dest;

	for (int i = 0; i < map->num_vertices; i++)
	{
		pos = pos_to_pixels(game->editor, map->vertices[i].x, map->vertices[i].y);
		SDL_RenderFillCircle(game->window->renderPTR, pos.x, pos.y, 5, color);
	}

	for (int i = 0; i < map->num_walls; i++)
	{
		t_wall *wall = &map->walls[i];

		if (wall->v1 < 0 || wall->v1 >= map->num_vertices || wall->v2 < 0 || wall->v2 >= map->num_vertices)
			continue;

		pos = pos_to_pixels(game->editor, map->vertices[wall->v1].x, map->vertices[wall->v1].y);
		dest = pos_to_pixels(game->editor, map->vertices[wall->v2].x, map->vertices[wall->v2].y);
		SDL_RenderDrawLineF(game->window->renderPTR, pos.x, pos.y, dest.x, dest.y);
	}

	return ;
}
