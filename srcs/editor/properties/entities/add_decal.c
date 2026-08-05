/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_decal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 18:05:41 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/05 17:43:11 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static t_tex	png_to_tex(t_png *png)
{
	t_tex		tex;
	int			bpp;
	__uint8_t	*px;

	tex.w = (int)png->w;
	tex.h = (int)png->h;
	tex.colors = calloc((size_t)tex.w * tex.h, sizeof(t_RGB));
	bpp = png->IHDR.bytes_per_pixel;
	for (__uint32_t y = 0; y < png->h; y++)
	{
		for (__uint32_t x = 0; x < png->w; x++)
		{
			px = &png->buf[y][x * bpp];
			if (png->IHDR.color_type == 6)
				tex.colors[y * tex.w + x] = (t_RGB){px[0], px[1], px[2], px[3]};
			else if (png->IHDR.color_type == 2)
				tex.colors[y * tex.w + x] = (t_RGB){px[0], px[1], px[2], 255};
			else if (png->IHDR.color_type == 4)
				tex.colors[y * tex.w + x] = (t_RGB){px[0], px[0], px[0], px[1]};
			else
				tex.colors[y * tex.w + x] = (t_RGB){px[0], px[0], px[0], 255};
		}
	}
	return (tex);
}

static void	free_png_buf(t_png *png)
{
	for (__uint32_t y = 0; y < png->h; y++)
		free(png->buf[y]);
	free(png->buf);
}

static float	project_on_wall(t_map *map, t_wall *wall, t_vect2 pos, float len)
{
	t_vect2	v1;
	t_vect2	dir;

	v1 = map->vertices[wall->v1];
	dir.x = (map->vertices[wall->v2].x - v1.x) / len;
	dir.y = (map->vertices[wall->v2].y - v1.y) / len;
	return ((pos.x - v1.x) * dir.x + (pos.y - v1.y) * dir.y);
}

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

void	add_decal(t_game *game, t_map *map, char *png_file, float height, t_vect2 pos)
{
	int		wall_idx;
	t_wall	*wall;
	t_decal	*decal;
	t_png	png;
	float	center_u;
	float	len;

	wall_idx = get_wall_index(map, pos.x, pos.y);
	if (wall_idx < 0)
		return ;
	wall = &map->walls[wall_idx];
	len = dist_vect(map->vertices[wall->v1], map->vertices[wall->v2]);
	if (len <= 0.0f || height <= 0.0f)
		return ;
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
	decal->width = decal->height * ((float)decal->texture.w / (float)decal->texture.h);
	center_u = project_on_wall(map, wall, pos, len) - decal->width * 0.5f;
	decal->u_offset = SDL_clamp(center_u, 0.0f, len - decal->width);
	decal->wall_idx = wall_idx;
	decal->z_bottom = 1.0f;
	decal->pos = pos;
	decal->elev_sector = game->editor->switch_sector;
	map->num_decals++;
}
