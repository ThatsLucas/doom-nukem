/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_spawn_props.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:23:16 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:23:32 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/GUI.h"

static void	init_prop_fields(t_entity *e, t_map *map, t_vect2 pos)
{
	e->type = ENTITY_PROP;
	e->status = E_STATUS_IDLE;
	e->x = pos.x;
	e->y = pos.y;
	e->z = get_plane_z(map->sectors[e->sector].floor_plane, e->x, e->y);
	e->dir_x = 1.0f;
	e->dir_y = 0.0f;
	e->hp = 0;
	e->speed = 0.0f;
	e->vision_range = 0.0f;
	e->vision_angle = 0.0f;
	e->attack_range = 0;
	e->fire_rate = 0;
	e->damage = 0;
	e->last_shot_time = 0;
	e->notif = NULL;
	e->hitbox = 0.4;
	e->num_frames = 0;
	e->textures = NULL;
	e->texture_shoot = NULL;
	e->texture_dead = NULL;
}

static void	load_prop_texture(t_game *game, t_entity *e, char *png_path)
{
	t_png	png;

	png.w = 0;
	png.h = 0;
	png.path = ft_strdup(png_path);
	if (!png.path)
		exit_game(game, "Failed to strdup prop texture path");
	if (!process_png(&png))
		exit_game(game, "Failed to load prop texture");
	e->texture = create_sprite(&png);
	if (!e->texture)
		exit_game(game, "Failed to create prop image");
}

int	spawn_props(t_game *game, t_vect2 pos, char *png_path)
{
	t_entity	e;
	t_map		*map;

	map = game->map;
	if (!map)
		return (0);
	e.sector = find_sector(map, pos);
	if (e.sector == -1)
		return (0);
	init_prop_fields(&e, map, pos);
	load_prop_texture(game, &e, png_path);
	add_entity(game, &game->entities, e);
	return (1);
}
