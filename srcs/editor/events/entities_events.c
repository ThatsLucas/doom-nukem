/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 11:57:58 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 13:10:31 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"
#include <math.h>

static int	is_valid_entity_pos(t_map *map, t_vect2 pos)
{
	if (!map)
		return (0);
	if (pos.x < 0.0f || pos.x >= map->mapSize.x)
		return (0);
	if (pos.y < 0.0f || pos.y >= map->mapSize.y)
		return (0);
	return (find_sector(map, pos) >= 0);
}

static void	normalize_direction(t_vect2 *dir)
{
	float	length;

	if (!dir)
		return ;
	length = sqrtf(dir->x * dir->x + dir->y * dir->y);
	if (length > 0.0f)
	{
		dir->x /= length;
		dir->y /= length;
	}
	else
	{
		dir->x = 1.0f;
		dir->y = 0.0f;
	}
}

/*
	Switch decals are placed on the second click.
	Returns 1 if the entity was a switch (handled), 0 otherwise.
*/
static int	place_switch(t_game *game, t_map *map, t_vect2 click_pos)
{
	t_editor	*editor = game->editor;

	if (!ft_strcmp(editor->entity_text, "Switch"))
	{
		if (add_decal(game, map, "assets/png/items/decals/switch.png", 0.5f, click_pos))
			return (1);
		editor->entity_step = 0;
		return (1);
	}
	if (!ft_strcmp(editor->entity_text, "Switch_Key"))
	{
		if (add_decal(game, map, "assets/png/items/decals/switch_key.png", 0.5f, click_pos))
			return (1);
		editor->entity_step = 0;
		map->decals[map->num_decals - 1].need_key = 1;
		return (1);
	}
	return (0);
}

/* Second click: add the entity at entity_base, looking toward click_pos */
static void	place_map_entity(t_game *game, t_map *map, t_vect2 click_pos)
{
	t_editor	*editor = game->editor;
	t_map_ent	*m;
	t_vect2		dir;

	if (map->num_entities == map->cap_entities)
		map_realloc(game, (void **)&map->entities, &map->cap_entities, sizeof(t_map_ent));
	m = &map->entities[map->num_entities];
	m->pos = editor->entity_base;
	m->id = editor->selected_entity;
	m->type = editor->selected_entity_type;
	m->sector_id = find_sector(map, m->pos);
	if (m->sector_id < 0)
	{
		editor->entity_step = 0;
		return ;
	}
	dir.x = click_pos.x - m->pos.x;
	dir.y = click_pos.y - m->pos.y;
	normalize_direction(&dir);
	m->ang = dir;
	map->num_entities++;
	editor->entity_step = 0;
}

/* Second click with the player type: set the player spawn and direction */
static void	place_player_spawn(t_editor *editor, t_map *map, t_vect2 click_pos)
{
	t_vect2	dir;

	dir.x = click_pos.x - editor->entity_base.x;
	dir.y = click_pos.y - editor->entity_base.y;
	normalize_direction(&dir);
	map->player_spawn.x = editor->entity_base.x;
	map->player_spawn.y = editor->entity_base.y;
	map->player_dir = dir;
	editor->entity_step = 0;
}

/* First click: remember the base position (windows are placed directly) */
static void	start_entity_placement(t_game *game, t_map *map, t_vect2 click_pos)
{
	t_editor	*editor = game->editor;

	if (!ft_strcmp(editor->entity_text, "Window"))
	{
		add_decal(game, map, "assets/png/items/decals/window_tree.png", 2.0f, click_pos);
		return ;
	}
	if (is_valid_entity_pos(map, click_pos))
	{
		editor->entity_base = click_pos;
		editor->switch_sector = find_sector(editor->map, click_pos);
		editor->entity_step = 1;
	}
	else
		editor->entity_step = 0;
}

void	entities_events(t_game *game, SDL_Event *e)
{
	t_vect2		click_pos;
	t_map		*map;
	t_editor	*editor;

	if (!game || !game->editor || !e || !game->editor->map)
		return ;
	map = game->editor->map;
	editor = game->editor;
	check_button_pressed(game, editor->buttons_entities);
	if (e->button.button != SDL_BUTTON_LEFT)
		return ;
	click_pos = pixels_to_pos(editor, (float)e->button.x, (float)e->button.y);
	if (editor->entity_step == 1 && editor->selected_entity_type != 1)
	{
		if (!is_valid_entity_pos(map, editor->entity_base)
			|| !is_valid_entity_pos(map, click_pos))
		{
			editor->entity_step = 0;
			return ;
		}
		if (!place_switch(game, map, click_pos))
			place_map_entity(game, map, click_pos);
	}
	else if (editor->entity_step == 1 && editor->selected_entity_type == 1)
		place_player_spawn(editor, map, click_pos);
	else
		start_entity_placement(game, map, click_pos);
}
