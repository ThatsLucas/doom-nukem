/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 11:06:23 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/27 20:16:05 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static void	draw_slope_arrow(t_game *game, t_vect2 base, t_vect2 tip, t_RGB color)
{
	t_vect2	pb;
	t_vect2	pt;

	pb = pos_to_pixels(game->editor, base.x, base.y);
	pt = pos_to_pixels(game->editor, tip.x, tip.y);
	SDL_RenderFillCircle(game->window->renderPTR, (int)pb.x, (int)pb.y, 6, color);
	SDL_SetRenderDrawColor(game->window->renderPTR, color.r, color.g, color.b, color.alphaValue);
	SDL_RenderDrawLineF(game->window->renderPTR, pb.x, pb.y, pt.x, pt.y);
}

static void	draw_entity(t_game *game, t_vect2 base, t_vect2 dir, int type)
{
	t_vect2	pb;
	t_vect2	pt;
	t_RGB	color;
	float	length;

	if (type == 1)
		color = (t_RGB){0, 200, 0, 255};
	else if (type == 2)
		color = (t_RGB){255, 50, 255, 255};
	else if (type == 3)
		color = (t_RGB){153, 76, 0, 255};
	else if (type == 4)
		color = (t_RGB){0, 105, 205, 255};
	pb = pos_to_pixels(game->editor, base.x, base.y);
	length = sqrtf(dir.x * dir.x + dir.y * dir.y);
	if (length > 0.0f)
	{
		pt.x = base.x + 0.5f * dir.x / length;
		pt.y = base.y + 0.5f * dir.y / length;
	}
	else
	{
		pt.x = base.x;
		pt.y = base.y;
	}
	pt = pos_to_pixels(game->editor, pt.x, pt.y);
	SDL_RenderFillCircle(game->window->renderPTR, (int)pb.x, (int)pb.y, 6, color);
	SDL_SetRenderDrawColor(game->window->renderPTR, color.r, color.g, color.b, color.alphaValue);
	SDL_RenderDrawLineF(game->window->renderPTR, pb.x, pb.y, pt.x, pt.y);
}

static void	draw_slope_arrows(t_game *game)
{
	t_map				*map;
	t_editor_properties	*props;
	t_RGB				floor_color;
	t_RGB				ceil_color;
	t_RGB				preview_color;
	t_vect2				pb;
	int					mouseX;
	int					mouseY;
	int					i;

	map = game->editor->map;
	props = &game->editor->properties;
	floor_color = (t_RGB){0, 200, 80, 255};
	ceil_color = (t_RGB){80, 120, 255, 255};
	preview_color = (t_RGB){255, 200, 0, 255};

	i = 0;
	while (i < map->num_sectors)
	{
		if (map->sectors[i].has_floor_arrow)
			draw_slope_arrow(game, map->sectors[i].floor_arrow_base, map->sectors[i].floor_arrow_tip, floor_color);
		if (map->sectors[i].has_ceil_arrow)
			draw_slope_arrow(game, map->sectors[i].ceil_arrow_base, map->sectors[i].ceil_arrow_tip, ceil_color);
		i++;
	}

	if (game->editor->selected_tool == 2 && props->slope_step == 1)
	{
		SDL_GetMouseState(&mouseX, &mouseY);
		pb = pos_to_pixels(game->editor, props->slope_base.x, props->slope_base.y);
		SDL_RenderFillCircle(game->window->renderPTR, (int)pb.x, (int)pb.y, 6, preview_color);
		SDL_SetRenderDrawColor(game->window->renderPTR, 255, 200, 0, 255);
		SDL_RenderDrawLineF(game->window->renderPTR, pb.x, pb.y, (float)mouseX, (float)mouseY);
	}
}

/*	Affiche la map dans l'editor	*/
void	display_editor_map(t_game *game)
{
	t_map		*map = game->editor->map;
	t_RGB		color = {0, 10, 59, 255};
	t_RGB		selected_color = {207, 10, 59, 255};
	t_vect2		pos, dest, mousePos, *selected_vertice;
	int			mouseX, mouseY, index_wall_hover;
	t_map_ent	*e;

	SDL_GetMouseState(&mouseX, &mouseY);
	mousePos = pixels_to_pos(game->editor, mouseX, mouseY);
	selected_vertice = get_clicked_vertice(game, mousePos.x, mousePos.y);
	index_wall_hover = get_wall_index(map, mousePos.x, mousePos.y);

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

	draw_slope_arrows(game);

	for (int i = 0; i < map->num_entities; i++)
	{
		e = &map->entities[i];
		draw_entity(game, e->pos, e->ang, e->type);
	}

	draw_entity(game, map->player_spawn, map->player_dir, 1);

	for (int i = 0; i < map->num_decals; i++)
	{
		t_vect2	decal_pos = pos_to_pixels(game->editor, map->decals[i].pos.x, map->decals[i].pos.y);
		SDL_RenderFillCircle(game->window->renderPTR, decal_pos.x, decal_pos.y, 6, color);
	}

	return ;
}
