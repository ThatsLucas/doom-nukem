/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 16:14:16 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/17 15:47:10 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static int	read_full(int fd, void *buf, size_t size)
{
	ssize_t	r;

	if (size == 0)
		return (0);
	r = read(fd, buf, size);
	if (r < 0 || (size_t)r != size)
		return (-1);
	return (0);
}

static int	load_one_wall(t_wall *w, int fd)
{
	if (read_full(fd, &w->v1, sizeof(int))
		|| read_full(fd, &w->v2, sizeof(int))
		|| read_full(fd, &w->next_sector, sizeof(int))
		|| read_full(fd, &w->length, sizeof(float))
		|| read_full(fd, &w->mirror, sizeof(int))
		|| read_full(fd, &w->tex_mid, sizeof(int))
		|| read_full(fd, &w->tex_upper, sizeof(int))
		|| read_full(fd, &w->tex_lower, sizeof(int))
		|| read_full(fd, &w->alpha, sizeof(float)))
		return (-1);
	w->sector_front = -1;
	w->sector_back = -1;
	return (0);
}

static int	load_vertices_walls(t_map *map, int fd)
{
	int	i;

	if (read_full(fd, &map->num_vertices, sizeof(int)))
		return (-1);
	if (map->num_vertices < 0 || map->num_vertices > INT_MAX)
		return (-1);
	map->vertices = ft_calloc(map->num_vertices, sizeof(t_vect2));
	if (!map->vertices)
		return (-1);
	if (read_full(fd, map->vertices, sizeof(t_vect2) * map->num_vertices))
		return (-1);
	if (read_full(fd, &map->num_walls, sizeof(int)))
		return (-1);
	if (map->num_walls < 0 || map->num_walls > INT_MAX)
		return (-1);
	map->walls = ft_calloc(map->num_walls, sizeof(t_wall));
	if (!map->walls)
		return (-1);
	i = 0;
	while (i < map->num_walls)
	{
		if (load_one_wall(&map->walls[i], fd))
			return (-1);
		i++;
	}
	return (0);
}

static int	load_one_sector(t_sector *s, int fd)
{
	if (read_full(fd, &s->num_walls, sizeof(int)))
		return (-1);
	if (s->num_walls < 0 || s->num_walls > INT_MAX)
		return (-1);
	s->walls = ft_calloc(s->num_walls, sizeof(int));
	if (!s->walls)
		return (-1);
	if (read_full(fd, s->walls, sizeof(int) * s->num_walls))
		return (-1);
	if (read_full(fd, &s->floor_plane, sizeof(t_plane))
		|| read_full(fd, &s->ceil_plane, sizeof(t_plane))
		|| read_full(fd, &s->floor_tex, sizeof(int))
		|| read_full(fd, &s->ceil_tex, sizeof(int))
		|| read_full(fd, &s->sky_tex, sizeof(int))
		|| read_full(fd, &s->light_level, sizeof(int)))
		return (-1);
	if (read_full(fd, &s->floor_arrow_base, sizeof(t_vect2))
		|| read_full(fd, &s->floor_arrow_tip, sizeof(t_vect2))
		|| read_full(fd, &s->ceil_arrow_base, sizeof(t_vect2))
		|| read_full(fd, &s->ceil_arrow_tip, sizeof(t_vect2))
		|| read_full(fd, &s->has_floor_arrow, sizeof(int))
		|| read_full(fd, &s->has_ceil_arrow, sizeof(int)))
		return (-1);
	return (0);
}

static int	load_sectors(t_map *map, int fd)
{
	int	i;

	if (read_full(fd, &map->num_sectors, sizeof(int)))
		return (-1);
	if (map->num_sectors < 0 || map->num_sectors > INT_MAX)
		return (-1);
	map->sectors = ft_calloc(map->num_sectors, sizeof(t_sector));
	if (!map->sectors)
		return (-1);
	i = 0;
	while (i < map->num_sectors)
	{
		if (load_one_sector(&map->sectors[i], fd))
			return (-1);
		i++;
	}
	return (0);
}

static int	load_textures(t_map *map, int fd)
{
	int		i;
	t_tex	*t;

	if (read_full(fd, &map->num_textures, sizeof(int)))
		return (-1);
	if (map->num_textures < 0 || map->num_textures > INT_MAX)
		return (-1);
	map->textures = ft_calloc(map->num_textures, sizeof(t_tex));
	if (!map->textures)
		return (-1);
	i = 0;
	while (i < map->num_textures)
	{
		t = &map->textures[i];
		if (read_full(fd, &t->w, sizeof(int))
			|| read_full(fd, &t->h, sizeof(int)))
			return (-1);
		if (t->w <= 0 || t->h <= 0 || t->w > INT_MAX || t->h > INT_MAX)
			return (-1);
		t->colors = ft_calloc((size_t)t->w * t->h, sizeof(t_RGB));
		if (!t->colors)
			return (-1);
		if (read_full(fd, t->colors, sizeof(t_RGB) * (size_t)t->w * t->h))
			return (-1);
		i++;
	}
	return (0);
}

static int	load_entity(t_map *map, int fd)
{
	if (read_full(fd, &map->player_spawn, sizeof(t_vect2)))
		return (-1);
	if (read_full(fd, &map->player_dir, sizeof(t_vect2)))
		return (-1);
	return (0);
}

static void	load_elevators(t_map *map, int fd)
{
	int	direction;
	int	level_size;

	for (int i = 0; i < map->num_sectors; ++i)
	{
		if (read_full(fd, &direction, sizeof(int))
			|| read_full(fd, &level_size, sizeof(int)))
			return ;
		map->sectors[i].direction = direction;
		map->sectors[i].levelSize = level_size;
	}

	return ;
}

t_map	*load_map(char *name, t_game *game)
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
		|| load_textures(map, fd) || load_entity(map, fd))
	{
		close(fd);
		free_map(map);
		return (NULL);
	}
	load_elevators(map, fd);
	close(fd);
	map->cap_textures = map->num_textures;
	map->cap_sectors = map->num_sectors;
	map->cap_walls = map->num_walls;
	map->cap_vertices = map->num_vertices;
	precompute_next_sectors(map);
	precompute_lengths(map);

	game->ply->pos = map->player_spawn;
	game->ply->dir = map->player_dir;
	game->ply->sector = find_sector(map, game->ply->pos);
	game->ply->z = get_plane_z(map->sectors[game->ply->sector].floor_plane, game->ply->pos.x, game->ply->pos.y);

	return (map);
}

void	load_editor_map(t_game *game)
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
		ft_printf("Can't load a map: name needed\n");
		return ;
	}
	map = load_map(s, game);
	if (map)
	{
		free_map(game->editor->map);
		game->editor->map = map;
		fit_grid_view(game);
	}
	else
		ft_printf("Error with loading '%s'\n", s);
}

