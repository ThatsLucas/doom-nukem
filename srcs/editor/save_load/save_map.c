/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:07:13 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:17:33 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Enregistre une carte dans un fichier. */
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
	save_spawn_and_decals(map, fd);
	save_elevators(map, fd);
	save_entities(map, fd);

	ft_printf("Map Saved !\n");

	close(fd);
	return (0);
}

/* Enregistre la carte de l’éditeur sous le nom saisi. */
void	save_editor_map(t_game *game)
{
	char			*s;

	s = get_map_name_input(game);
	if (!s || !ft_strlen(s))
	{
		ft_printf("Can't save the map: name needed\n");
		return ;
	}
	save_map(s, game->editor->map);
}
