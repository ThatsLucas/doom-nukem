/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 11:06:23 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/04 17:11:08 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/*	Affiche la map dans l'editor	*/
void	display_editor_map(t_game *game)
{
	t_map		*map = game->editor->map;
	t_RGB		color = {0, 10, 59, 255};
	t_RGB		selected_color = {207, 10, 59, 255};
	t_vect2		pos, dest, mousePos, *selected_vertice;
	int			mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);
	mousePos = pixels_to_pos(game->editor, mouseX, mouseY);
	selected_vertice = get_clicked_vertice(game, mousePos.x, mousePos.y);

	for (int i = 0; i < map->num_vertices; i++)
	{
		pos = pos_to_pixels(game->editor, map->vertices[i].x, map->vertices[i].y);
		if (selected_vertice == &map->vertices[i])
			SDL_RenderFillCircle(game->window->renderPTR, pos.x, pos.y, 5, selected_color);
		else
			SDL_RenderFillCircle(game->window->renderPTR, pos.x, pos.y, 5, color);
	}

	SDL_SetRenderDrawColor(game->window->renderPTR, 0, 10, 59, 255);
	for (int i = 0; i < map->num_walls; i++)
	{
		t_wall *wall = &map->walls[i];

		if (wall->v1 < 0 || wall->v1 >= map->num_vertices || wall->v2 < 0 || wall->v2 >= map->num_vertices)
			continue;

		pos = pos_to_pixels(game->editor, map->vertices[wall->v1].x, map->vertices[wall->v1].y);
		dest = pos_to_pixels(game->editor, map->vertices[wall->v2].x, map->vertices[wall->v2].y);
		if (point_on_segment(mousePos, map->vertices[wall->v1], map->vertices[wall->v2], 0.1f))
			SDL_SetRenderDrawColor(game->window->renderPTR, 207, 10, 59, 255);
		else
			SDL_SetRenderDrawColor(game->window->renderPTR, 0, 10, 59, 255);
		SDL_RenderDrawLineF(game->window->renderPTR, pos.x, pos.y, dest.x, dest.y);
	}

	return ;
}
