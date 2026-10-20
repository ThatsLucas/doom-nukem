/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map_sections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:03:09 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:03:09 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Enregistre les données d’un mur. */
static void	save_one_wall(t_wall *w, int fd)
{
	write(fd, &w->v1, sizeof(int));
	write(fd, &w->v2, sizeof(int));
	write(fd, &w->next_sector, sizeof(int));
	write(fd, &w->length, sizeof(float));
	write(fd, &w->mirror, sizeof(int));
	write(fd, &w->tex_mid, sizeof(int));
	write(fd, &w->tex_upper, sizeof(int));
	write(fd, &w->tex_lower, sizeof(int));
	write(fd, &w->alpha, sizeof(float));
}

/* Enregistre les sommets et les murs. */
void	save_vertices_walls(t_map *map, int fd)
{
	int	i;

	write(fd, &map->num_vertices, sizeof(int));
	write(fd, map->vertices, sizeof(t_vect2) * map->num_vertices);
	write(fd, &map->num_walls, sizeof(int));
	i = 0;
	while (i < map->num_walls)
	{
		save_one_wall(&map->walls[i], fd);
		i++;
	}
	return ;
}

/* Enregistre les secteurs. */
void	save_sectors(t_map *map, int fd)
{
	t_sector	s;

	write(fd, &map->num_sectors, sizeof(int));
	for (int i = 0; i < map->num_sectors; ++i)
	{
		s = map->sectors[i];

		write(fd, &s.num_walls, sizeof(int));
		write(fd, s.walls, sizeof(int) * s.num_walls);

		write(fd, &s.floor_plane, sizeof(t_plane));
		write(fd, &s.ceil_plane, sizeof(t_plane));
		write(fd, &s.floor_tex, sizeof(int));
		write(fd, &s.ceil_tex, sizeof(int));
		write(fd, &s.sky_tex, sizeof(int));
		write(fd, &s.light_level, sizeof(int));
		write(fd, &s.floor_arrow_base, sizeof(t_vect2));
		write(fd, &s.floor_arrow_tip, sizeof(t_vect2));
		write(fd, &s.ceil_arrow_base, sizeof(t_vect2));
		write(fd, &s.ceil_arrow_tip, sizeof(t_vect2));
		write(fd, &s.has_floor_arrow, sizeof(int));
		write(fd, &s.has_ceil_arrow, sizeof(int));
	}

	return ;
}

/* Enregistre les textures. */
void	save_textures(t_map *map, int fd)
{
	t_tex	t;

	write(fd, &map->num_textures, sizeof(int));
	for (int i = 0; i < map->num_textures; ++i)
	{
		t = map->textures[i];

		write(fd, &t.w, sizeof(int));
		write(fd, &t.h, sizeof(int));
		write(fd, t.colors, sizeof(t_RGB) * t.h * t.w);
	}

	return ;
}

/* Enregistre le point d’apparition et les décalques. */
void	save_spawn_and_decals(t_map *map, int fd)
{
	t_decal	d;

	write(fd, &map->player_spawn, sizeof(t_vect2));
	write(fd, &map->player_dir, sizeof(t_vect2));

	write(fd, &map->num_decals, sizeof(int));
	for (int i = 0; i < map->num_decals; ++i)
	{
		d = map->decals[i];

		write(fd, &d.wall_idx, sizeof(int));
		write(fd, &d.u_offset, sizeof(float));
		write(fd, &d.width, sizeof(float));
		write(fd, &d.z_bottom, sizeof(float));
		write(fd, &d.height, sizeof(float));
		write(fd, &d.elev_sector, sizeof(int));
		write(fd, &d.sector_id, sizeof(int));
		write(fd, &d.need_key, sizeof(int));
		write(fd, &d.pos, sizeof(t_vect2));
		write(fd, &d.texture.w, sizeof(int));
		write(fd, &d.texture.h, sizeof(int));
		write(fd, d.texture.colors, sizeof(t_RGB) * d.texture.w * d.texture.h);
	}

	return ;
}

/* Enregistre les ascenseurs. */
void	save_elevators(t_map *map, int fd)
{
	for (int i = 0; i < map->num_sectors; ++i)
	{
		write(fd, &map->sectors[i].direction, sizeof(int));
		write(fd, &map->sectors[i].levelSize, sizeof(int));
	}

	return ;
}

/* Enregistre les entités. */
void	save_entities(t_map *map, int fd)
{
	write(fd, &map->num_entities, sizeof(int));
	for (int i = 0; i < map->num_entities; ++i)
	{
		write(fd, &map->entities[i].pos, sizeof(t_vect2));
		write(fd, &map->entities[i].ang, sizeof(t_vect2));
		write(fd, &map->entities[i].sector_id, sizeof(int));
		write(fd, &map->entities[i].id, sizeof(int));
		write(fd, &map->entities[i].type, sizeof(int));
	}
}
