/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 09:59:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/29 23:02:58 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/*	Initialisation de la map de l'Editor	*/
void	init_editor_map(t_game *game)
{
	t_map	*map = NULL;

	game->editor->map = calloc(1, sizeof(t_map));
	if (!game->editor->map)
		exit_game(game, "editor: cant calloc map");

	map = game->editor->map;

	map->vertices = calloc(16, sizeof(t_vect2));
	map->cap_vertices = 16;

	map->sectors = calloc(4, sizeof(t_sector));
	map->cap_sectors = 4;

	map->walls = calloc(8, sizeof(t_wall));
	map->cap_walls = 8;

	if (!map->vertices || !map->sectors || !map->walls)
		exit_game(game, "editor: init_editor_map calloc failed");

	return ;
}

/*	Réallouer le tableau dynamique de la map	*/
void	map_realloc(t_game *game, void **pointer, int *cap, unsigned int sizeofone)
{
	int		new_cap;
	void	*new_ptr;

	new_cap = *cap * 2;
	new_ptr = realloc(*pointer, new_cap * sizeofone);

	if (!new_ptr)
		exit_game(game, "map_realloc failed");

	*pointer = new_ptr;
	*cap = new_cap;

	return ;
}
