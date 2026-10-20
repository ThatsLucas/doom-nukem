/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_decal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 18:05:41 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 11:36:44 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"
#include "GUI/GUI.h"

/* Libère le tampon de l’image PNG. */
static void	free_png_buf(t_png *png)
{
	for (__uint32_t y = 0; y < png->h; y++)
		free(png->buf[y]);
	free(png->buf);
}

/* Projette la position du décalque sur le mur. */
static float	project_on_wall(t_map *map, t_wall *wall, t_vect2 pos, float len)
{
	t_vect2	v1;
	t_vect2	dir;

	v1 = map->vertices[wall->v1];
	dir.x = (map->vertices[wall->v2].x - v1.x) / len;
	dir.y = (map->vertices[wall->v2].y - v1.y) / len;
	return ((pos.x - v1.x) * dir.x + (pos.y - v1.y) * dir.y);
}

/* Supprime le décalque proche de la position. */
int	suppress_decal(t_game *game, t_vect2 pos)
{
	t_map	*map;
	t_decal	*d;

	map = game->editor->map;
	for (int i = 0; i < map->num_decals; ++i)
	{
		d = &map->decals[i];
		if (dist_vect(pos, d->pos) < 0.1f)
		{
			free(d->texture.colors);
			ft_memmove(d, d + 1, sizeof(t_decal) * (map->num_decals - i - 1));
			map->num_decals--;
			return (1);
		}
	}
	return (0);
}

/* Place le décalque au centre de la position projetée sur le mur. */
static void	place_decal(t_game *game, t_map *map, int wall_idx, t_vect2 pos, float len)
{
	t_decal	*decal = &map->decals[map->num_decals];
	float	center_u;

	decal->width = decal->height * ((float)decal->texture.w / (float)decal->texture.h);
	center_u = project_on_wall(map, &map->walls[wall_idx], pos, len) - decal->width * 0.5f;
	decal->u_offset = SDL_clamp(center_u, 0.0f, len - decal->width);
	decal->wall_idx = wall_idx;
	decal->z_bottom = 1.0f;
	decal->pos = pos;
	decal->elev_sector = game->editor->switch_sector;
	decal->sector_id = find_sector(game->editor->map, pos);
	decal->need_key = 0;
}

/* Ajoute un décalque sur le mur le plus proche. */
int	add_decal(t_game *game, t_map *map, char *png_file, float height, t_vect2 pos)
{
	int		wall_idx;
	t_wall	*wall;
	t_decal	*decal;
	t_png	png;
	float	len;

	wall_idx = get_wall_index(map, pos.x, pos.y);
	if (wall_idx < 0)
		return (1);
	wall = &map->walls[wall_idx];
	len = dist_vect(map->vertices[wall->v1], map->vertices[wall->v2]);
	if (len <= 0.0f || height <= 0.0f)
		return (1);
	png.path = ft_strdup(png_file);
	if (!png.path)
		exit_game(game, "Failed to strdup decal texture path");
	if (!process_png(&png))
		exit_game(game, "Failed to load decal texture");
	if (map->num_decals == map->cap_decals)
		map_realloc(game, (void **)&map->decals, &map->cap_decals, sizeof(t_decal));
	decal = &map->decals[map->num_decals];
	decal->texture = png_to_tex(&png);
	free_png_buf(&png);
	decal->height = height;
	place_decal(game, map, wall_idx, pos, len);
	map->num_decals++;

	return (0);
}
