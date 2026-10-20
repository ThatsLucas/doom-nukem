/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_create_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:40:40 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 11:40:40 by aabouyaz         ###   ########.fr       */
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
	t_png	png;
	char	path[200];

	e->num_frames = 8;
	e->textures = malloc(sizeof(t_tex *) * e->num_frames);
	if (!e->textures)
		exit_game(game, "Failed to malloc pnj frames");

	for (int i = 0; i < e->num_frames; i++)
	{
		png.w = w;
		png.h = h;
		sprintf(path, "%s%d.png", prefix, i + 1);
		png.path = ft_strdup(path);
		if (!png.path)
			exit_game(game, "Failed to strdup pnj frame");
		if (!process_png(&png))
			exit_game(game, "Failed to process pnj frame");
		e->textures[i] = create_sprite(&png);
		if (!e->textures[i])
			exit_game(game, "Failed to create image pnj frame");
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
	t_png	png;
	t_tex	*tex;

	png.w = w;
	png.h = h;
	png.path = ft_strjoin(dir, file);
	if (!png.path)
		exit_game(game, "Failed to join entity texture path");
	if (!process_png(&png))
		exit_game(game, "Failed to load entity texture");
	tex = create_sprite(&png);
	if (!tex)
		exit_game(game, "Failed to create entity image");
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
