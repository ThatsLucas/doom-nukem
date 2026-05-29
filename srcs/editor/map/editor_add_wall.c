/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_add_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:31:55 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/29 23:02:33 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static int	get_alpha(t_game *game)
{
	t_list			*current = game->editor->text_inputs;
	t_text_input	*input;

	while (current)
	{
		input = (t_text_input *)current->content;
		if (!ft_strcmp(input->name, "walls_alpha"))
			return (SDL_clamp(ft_atoi(input->text), 0, 255));

		current = current->next;
	}

	return (255);
}

static int	wall_already_exist(t_game *game, int v1, int v2)
{
	t_map	*map = game->editor->map;
	t_wall	*wall;

	for (int i = 0; i < map->num_walls; ++i)
	{
		wall = &map->walls[i];
		if (wall->v1 == v1 && wall->v2 == v2)
			return (1);
		if (wall->v1 == v2 && wall->v2 == v1)
			return (1);
	}

	return (0);
}

static float	inter_segments(t_vect2 P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res)
{
	t_vect2	qp;
	float	rs, t, u;

	rs = vect2_product(r, s);
	if (fabsf(rs) < 1e-6f)		/* parallèles ou colinéaires */
		return (-1);
	qp = edge(P, Q);
	t = vect2_product(qp, s) / rs;
	u = vect2_product(qp, r) / rs;

	if (t <= 0.01f || t >= 1.0f - 0.01f || u <= 0.01f || u >= 1.0f - 0.01f)
		return (-1);
	res->x = P.x + t * r.x;
	res->y = P.y + t * r.y;
	return (t);
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

static int	split_wall(t_game *game, int wall_a, int wall_b, int vmid)
{
	t_map	*map = game->editor->map;
	t_wall	*a1, *a2, *b1, *b2;
	int		b2_index;

	if (wall_a < 0 || wall_a >= map->num_walls || wall_b < 0 || wall_b >= map->num_walls)
		exit_game(game, "split_wall: invalid wall index");

	while (map->num_walls + 2 > map->cap_walls)
		map_realloc(game, (void **)&map->walls, &map->cap_walls, sizeof(t_wall));

	b2_index = map->num_walls + 1;
	a1 = &map->walls[wall_a];
	b1 = &map->walls[wall_b];
	a2 = &map->walls[map->num_walls];
	b2 = &map->walls[b2_index];

	a2->v1 = vmid;
	b2->v1 = vmid;
	a2->v2 = a1->v2;
	b2->v2 = b1->v2;
	a1->v2 = vmid;
	b1->v2 = vmid;

	copy_wall_info(a1, a2);
	copy_wall_info(b1, b2);

	map->num_walls += 2;

	return (b2_index);
}

/*	Si un mur croise un autre on le split	*/
static int	check_intersections(t_game *game, t_map *map, int new_wall_id, int walls_num)
{
	t_vect2	a, b, c, d;
	t_vect2	r, s, inter;
	t_wall	*wall = &map->walls[new_wall_id];
	int		half_wall_idx;

	a = map->vertices[wall->v1];
	b = map->vertices[wall->v2];

	for (int i = 0; i < walls_num; ++i)
	{
		c = map->vertices[map->walls[i].v1];
		d = map->vertices[map->walls[i].v2];
		r = edge(a, b);
		s = edge(c, d);
		if (inter_segments(a, r, c, s, &inter) >= 0.0f)
		{
			editor_add_vertice(game, inter.x, inter.y);
			half_wall_idx = split_wall(game, i, new_wall_id, map->num_vertices - 1);
			check_intersections(game, map, half_wall_idx, map->num_walls);
			check_intersections(game, map, new_wall_id, map->num_walls);

			return (1);
		}
	}
	return (0);
}

/*	Ajouter un mur à la map	*/
void	editor_add_wall(t_game *game, int v1, int v2)
{
	t_map	*map = game->editor->map;
	t_wall	*wall;

	if (wall_already_exist(game, v1, v2))
		return ;

	if (map->num_walls == map->cap_walls)
		map_realloc(game, (void **)&map->walls, &map->cap_walls, sizeof(t_wall));

	wall = &map->walls[map->num_walls];
	wall->v1 = v1;
	wall->v2 = v2;
	wall->next_sector = -1;
	wall->alpha = get_alpha(game);

	// base pour linstant il faudra ajouter le reste: textures et tout

	map->num_walls++;

	if (check_intersections(game, map, map->num_walls - 1, map->num_walls - 1))
		compute_sectors(map);

	return ;
}
