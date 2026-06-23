/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:07:13 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/23 16:41:14 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static void	save_vertices_walls(t_map *map, int fd)
{
	write(fd, &map->num_vertices, sizeof(int));
	write(fd, map->vertices, sizeof(t_vect2) * map->num_vertices);
	write(fd, &map->num_walls, sizeof(int));
	write(fd, map->walls, sizeof(t_wall) * map->num_walls);

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
	write(fd, &map->player_spawn, sizeof(t_vect2));
	write(fd, &map->player_z, sizeof(float));

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

	save_vertices_walls(map, fd);
	save_sectors(map, fd);
	save_textures(map, fd);
	save_entity(map, fd);

	ft_printf("Map Saved !");

	close(fd);
	return (0);
}

void	save_editor_map(t_game *game)
{
	t_list			*current = game->editor->text_inputs;
	t_text_input	*input;
	char			*s;

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

	precompute_next_sectors(game->editor->map);
	precompute_mirrors(game->editor->map);
	precompute_lengths(game->editor->map);
	if (ft_strlen(s))
		save_map(s, game->editor->map);
	else
		ft_printf("Can't save the map: name needed\n");

	return ;
}
