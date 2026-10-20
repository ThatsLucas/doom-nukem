/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 11:06:23 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:16:53 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Vertices, plus the wall preview line when drawing a wall */
static void	draw_map_vertices(t_game *game, t_vect2 *selected_vertice, int mouseX, int mouseY)
{
	t_map	*map = game->editor->map;
	t_RGB	color = {0, 10, 59, 255};
	t_RGB	selected_color = {207, 10, 59, 255};
	t_vect2	pos;

	for (int i = 0; i < map->num_vertices; i++)
	{
		pos = pos_to_pixels(game->editor, map->vertices[i].x, map->vertices[i].y);
		if (selected_vertice == &map->vertices[i])
			SDL_RenderFillCircle(game->window->renderPTR, pos.x, pos.y, 5, selected_color);
		else
			SDL_RenderFillCircle(game->window->renderPTR, pos.x, pos.y, 5, color);

		if (game->editor->properties.last_vertex == i && game->editor->properties.draw_wall_active)
			SDL_RenderDrawLineF(game->window->renderPTR, pos.x, pos.y, mouseX, mouseY);
	}
}

/* All the walls, the hovered one in red */
static void	draw_map_walls(t_game *game, int index_wall_hover)
{
	t_map	*map = game->editor->map;
	t_vect2	pos, dest;

	SDL_SetRenderDrawColor(game->window->renderPTR, 0, 10, 59, 255);
	for (int i = 0; i < map->num_walls; i++)
	{
		t_wall *wall = &map->walls[i];

		if (wall->v1 < 0 || wall->v1 >= map->num_vertices || wall->v2 < 0 || wall->v2 >= map->num_vertices)
			continue;

		pos = pos_to_pixels(game->editor, map->vertices[wall->v1].x, map->vertices[wall->v1].y);
		dest = pos_to_pixels(game->editor, map->vertices[wall->v2].x, map->vertices[wall->v2].y);
		if (i == index_wall_hover)
			SDL_SetRenderDrawColor(game->window->renderPTR, 207, 10, 59, 255);
		else
			SDL_SetRenderDrawColor(game->window->renderPTR, 0, 10, 59, 255);
		SDL_RenderDrawLineF(game->window->renderPTR, pos.x, pos.y, dest.x, dest.y);
	}
}

/* Walls of the selected sector, in green */
static void	draw_selected_sector(t_game *game)
{
	t_map		*map = game->editor->map;
	t_sector	*sector;
	t_vect2		pos, dest;

	if (game->editor->properties.selected_sector < 0)
		return ;
	sector = &map->sectors[game->editor->properties.selected_sector];
	for (int i = 0; i < sector->num_walls; ++i)
	{
		t_wall *w = &map->walls[sector->walls[i]];

		if (w->v1 < 0 || w->v1 >= map->num_vertices || w->v2 < 0 || w->v2 >= map->num_vertices)
			continue;

		pos = pos_to_pixels(game->editor, map->vertices[w->v1].x, map->vertices[w->v1].y);
		dest = pos_to_pixels(game->editor, map->vertices[w->v2].x, map->vertices[w->v2].y);

		SDL_SetRenderDrawColor(game->window->renderPTR, 0, 255, 0, 255);
		SDL_RenderDrawLineF(game->window->renderPTR, pos.x, pos.y, dest.x, dest.y);
	}
}

/*	Affiche la map dans l'editor	*/
void	display_editor_map(t_game *game)
{
	t_vect2		mousePos, *selected_vertice;
	int			mouseX, mouseY, index_wall_hover;

	SDL_GetMouseState(&mouseX, &mouseY);
	mousePos = pixels_to_pos(game->editor, mouseX, mouseY);
	selected_vertice = get_clicked_vertice(game, mousePos.x, mousePos.y);
	index_wall_hover = get_wall_index(game->editor->map, mousePos.x, mousePos.y);

	draw_map_vertices(game, selected_vertice, mouseX, mouseY);
	draw_map_walls(game, index_wall_hover);
	draw_selected_sector(game);
	draw_map_slope_arrows(game);
	draw_map_entities(game);
}
