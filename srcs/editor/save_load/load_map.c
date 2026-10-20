/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 16:14:16 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/12 16:07:46 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static void	spawn_entities(t_map *map, t_game *game)
{
	t_map_ent	*e;

	for (int i = 0; i < map->num_entities; ++i)
	{
		e = &map->entities[i];
		if (e->type == 4 && e->id == 0)
			spawn_props(game, e->pos, "assets/png/items/props/barrel.png");
		else if (e->type == 2)
		{
			if (e->id == 0)
				create_pnj1(game, e->pos, e->ang);
			else if (e->id == 1)
				create_pnj2(game, e->pos, e->ang);
			else if (e->id == 2)
				create_pnj3(game, e->pos, e->ang);
			else if (e->id == 3)
				create_enemy1(game, e->pos);
			else if (e->id == 4)
				create_enemy2(game, e->pos);
			else if (e->id == 5)
				create_enemy3(game, e->pos);
			else if (e->id == 6)
				create_boss1(game, e->pos);
			else if (e->id == 7)
				create_boss2(game, e->pos);
			else if (e->id == 8)
				create_boss3(game, e->pos);
		}
	}

	return ;
}

/* Reads every section of the file, returns NULL on error */
static t_map	*read_map_file(char *name)
{
	char	*file;
	int		fd;
	t_map	*map;

	file = ft_strjoin("saves/", name);
	if (!file)
		return (NULL);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd < 0)
		return (NULL);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (close(fd), NULL);
	read_full(fd, &map->mapSize, sizeof(t_vect2));
	if (load_vertices_walls(map, fd) || load_sectors(map, fd)
		|| load_textures(map, fd) || load_spawn_and_decals(map, fd)
		|| load_elevators(map, fd) || load_entities(map, fd))
	{
		close(fd);
		free_map(map);
		return (NULL);
	}
	close(fd);
	return (map);
}

/* Puts the player on the spawn and creates the entities of the map */
static void	setup_game_map(t_game *game, t_map *map)
{
	game->entities.count = 0;
	ft_bzero(game->entities.list, sizeof(t_entity));
	game->map = map;
	game->ply->pos = map->player_spawn;
	game->ply->dir = map->player_dir;
	game->ply->sector = find_sector(map, game->ply->pos);
	game->ply->z = get_plane_z(map->sectors[game->ply->sector].floor_plane, game->ply->pos.x, game->ply->pos.y);
	spawn_entities(map, game);
	ft_printf("Entites: %d\n", game->entities.count);
}

t_map	*load_map(char *name, t_game *game, int editor)
{
	t_map	*map;

	map = read_map_file(name);
	if (!map)
		return (NULL);
	map->cap_textures = map->num_textures;
	map->cap_sectors = map->num_sectors;
	map->cap_walls = map->num_walls;
	map->cap_vertices = map->num_vertices;
	map->cap_decals = map->num_decals;
	precompute_next_sectors(map);
	precompute_lengths(map);

	if (!editor)
		setup_game_map(game, map);

	return (map);
}

void	load_editor_map(t_game *game)
{
	char			*s;
	t_map			*map;

	s = get_map_name_input(game);
	if (!s || !ft_strlen(s))
	{
		ft_printf("Can't load a map: name needed\n");
		return ;
	}
	map = load_map(s, game, 1);
	if (map)
	{
		free_map(game->editor->map);
		game->editor->map = map;
		fit_grid_view(game);
	}
	else
		ft_printf("Error with loading '%s'\n", s);
}
