/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_create_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:40:40 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/29 12:18:25 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/GUI.h"

/* Initialise les champs communs d’un PNJ. */
void	init_pnj_base(t_game *game, t_entity *e, t_vect2 pos, t_vect2 dir)
{
	e->type = ENTITY_PNJ;
	e->status = E_STATUS_IDLE;

	/*a changer pour trouver le bon secteur*/
	e->sector = find_sector(game->map, pos);
	if (e->sector == -1)
		exit_game(game, "Failed to find pnj sector");
	e->dir_x = dir.x;
	e->dir_y = dir.y;
	e->z = get_plane_z(game->map->sectors[e->sector].floor_plane, pos.x, pos.y);
	e->x = pos.x; e->y = pos.y;
	e->hp = 1000;
	e->hitbox = 1;
}

/* Charge les 8 images directionnelles d’un PNJ. */
void	load_entity_frames(t_game *game, t_entity *e, char *prefix, int w, int h)
{
	char	*path;

	e->num_frames = 8;
	e->textures = malloc(sizeof(t_tex *) * e->num_frames);
	if (!e->textures)
		exit_game(game, "Failed to malloc pnj frames");

	for (int i = 0; i < e->num_frames; i++)
	{
		char *index = ft_itoa(i + 1);
		char *result = ft_strjoin(prefix, index);
		path = ft_strjoin(result, ".png");
		e->textures[i] = get_cached_sprite(game, path, w, h);
		free(index);
		free(result);
		free(path);
	}

	e->texture = e->textures[0];
	e->sprite_w = (float)w;
	e->sprite_h = (float)h;
}

/* Initialise les champs communs d’un ennemi ou d’un boss. */
void	init_fighter_base(t_game *game, t_entity *e, t_entity_type type, t_vect2 pos)
{
	e->type = type;
	e->status = E_STATUS_IDLE;
	e->vision_angle = 360.0f;
	e->vision_range = 10.0f;
	e->dir_x = 1.0f;
	e->dir_y = 1.0f;
	e->num_frames = 0;
	e->textures = 0;
	e->x = pos.x;
	e->y = pos.y;
	e->hitbox = 1;
	e->last_shot_time = 0;

	/* pour voir z -> a changer */
	e->sector = find_sector(game->map, pos);
	if (e->sector == -1)
		exit_game(game, "Failed to find sector");
	e->z = get_plane_z(game->map->sectors[e->sector].floor_plane, pos.x, pos.y);
}

/* Charge la texture correspondant à l’état de l’entité. */
static t_tex	*load_state_texture(t_game *game, char *dir, char *file, int w, int h)
{
	char	*path;
	t_tex	*tex;

	path = ft_strjoin(dir, file);
	if (!path)
		exit_game(game, "Failed to join entity texture path");
	tex = get_cached_sprite(game, path, w, h);
	free(path);
	return (tex);
}

/* Charge les textures idle, tir et mort d’un combattant. */
void	load_fighter_textures(t_game *game, t_entity *e, char *dir, int size[4])
{
	e->texture = load_state_texture(game, dir, "idle.png", size[0], size[1]);
	e->texture_shoot = load_state_texture(game, dir, "shoot.png", size[0], size[1]);
	e->texture_dead = load_state_texture(game, dir, "dead.png", size[2], size[3]);
	e->sprite_w = (float)size[0];
	e->sprite_h = (float)size[1];
}
