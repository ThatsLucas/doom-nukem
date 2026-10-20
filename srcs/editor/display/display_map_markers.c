/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map_markers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:01:54 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:01:54 by aabouyaz         ###   ########.fr       */
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

void	draw_map_slope_arrows(t_game *game)
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

/* Entities, player spawn and decals */
void	draw_map_entities(t_game *game)
{
	t_map		*map = game->editor->map;
	t_RGB		color = {0, 10, 59, 255};
	t_map_ent	*e;

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
}
