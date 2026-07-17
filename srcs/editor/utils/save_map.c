/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:07:13 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/16 16:45:00 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

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

static void	save_vertices_walls(t_map *map, int fd)
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

static void	save_sectors(t_map *map, int fd)
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

static void	save_textures(t_map *map, int fd)
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

static void	save_entity(t_map *map, int fd)
{
	write(fd, &map->player_spawn, sizeof(t_vect3));

	return ;
}

static void	save_elevators(t_map *map, int fd)
{
	for (int i = 0; i < map->num_sectors; ++i)
	{
		write(fd, &map->sectors[i].direction, sizeof(int));
		write(fd, &map->sectors[i].levelSize, sizeof(int));
	}

	return ;
}

int	save_map(char *name, t_map *map)
{
	char	*file;

	file = ft_strjoin("saves/", name);

	int	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (fd < 0)
		return (1);

	write(fd, &map->mapSize, sizeof(t_vect2));
	save_vertices_walls(map, fd);
	save_sectors(map, fd);
	save_textures(map, fd);
	save_entity(map, fd);
	save_elevators(map, fd);

	ft_printf("Map Saved !\n");

	close(fd);
	return (0);
}

void	save_editor_map(t_game *game)
{
	t_list			*current = game->editor->text_inputs;
	t_text_input	*input;
	char			*s;
	t_map			*map;

	s = NULL;
	while (current)
	{
		input = (t_text_input *)current->content;
		if (!ft_strcmp("mapName", input->name))
		{
			s = input->text;
			break ;
		}
		current = current->next;
	}
	if (!s || !ft_strlen(s))
	{
		ft_printf("Can't save the map: name needed\n");
		return ;
	}
	map = game->editor->map;
	save_map(s, map);
}
