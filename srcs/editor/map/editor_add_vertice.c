/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_add_vertice.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:41:46 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/04 16:30:48 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/*	retourne la position de la vertice cliquée	*/
t_vect2	*get_clicked_vertice(t_game *game, float x, float y)
{
	t_map	*map = game->editor->map;
	t_vect2	pos = {.x = x, .y = y};
	float	dist;

	for (int i = 0; i < map->num_vertices; ++i)
	{
		dist = dist_vect(pos, map->vertices[i]);
		if (dist < 0.05f)
			return (&map->vertices[i]);
	}

	return (NULL);
}

static void	copy_wall_info(t_wall *src, t_wall *dest)
{
	dest->alpha			= src->alpha;
	dest->mirror		= src->mirror;
	dest->next_sector	= src->next_sector;
	dest->tex_lower		= src->tex_lower;
	dest->tex_mid		= src->tex_mid;
	dest->tex_upper		= src->tex_upper;

	return ;
}

static void	split_wall(t_game *game, t_map *map, int vmid, int idx)
{
	t_wall	*new, *wall;

	while (map->num_walls == map->cap_walls)
		map_realloc(game, (void **)&map->walls, &map->cap_walls, sizeof(t_wall));

	wall = &map->walls[idx];
	new = &map->walls[map->num_walls++];
	new->v2 = wall->v2;
	new->v1 = vmid;
	wall->v2 = vmid;
	copy_wall_info(wall, new);

	return ;
}

/*	Ajouter une vertice à la map	*/
int	editor_add_vertice(t_game *game, float x, float y)
{
	t_map	*map = game->editor->map;
	t_vect2	*vertice;
	int		index = -1;

	vertice = get_clicked_vertice(game, x, y);
	if (vertice)
		index = vertice - game->editor->map->vertices;
	if (index >= 0)
		return (index);

	if (map->num_vertices == map->cap_vertices)
		map_realloc(game, (void **)&map->vertices, &map->cap_vertices, sizeof(t_vect2));

	vertice = &map->vertices[map->num_vertices];
	vertice->x = x;
	vertice->y = y;

	for (int i = 0; i < map->num_walls; i++)
	{
		t_wall *wall = &map->walls[i];

		if (wall->v1 < 0 || wall->v1 >= map->num_vertices || wall->v2 < 0 || wall->v2 >= map->num_vertices)
			continue;

		if (point_on_segment(*vertice, map->vertices[wall->v1], map->vertices[wall->v2], 0.1f))
		{
			split_wall(game, game->editor->map, map->num_vertices, i);
			break ;
		}
	}

	return (map->num_vertices++);
}
