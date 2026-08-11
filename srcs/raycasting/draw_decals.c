/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_decals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 19:00:00 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 11:00:04 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI/GUI.h"

/* limite le decalque au rectangle [y_top_f, y_bot_f] borne par le mur visible */
static int	clamp_decal_band(t_ray *ray, int sH, float y_top_f, float y_bot_f, int *draw_top, int *draw_bot)
{
	*draw_top = (int)y_top_f;
	*draw_bot = (int)y_bot_f;
	if (*draw_top < ray->y_wall_top)
		*draw_top = ray->y_wall_top;
	if (*draw_bot > ray->y_wall_bot)
		*draw_bot = ray->y_wall_bot;
	if (*draw_top < ray->y_top)
		*draw_top = ray->y_top;
	if (*draw_bot > ray->y_bot)
		*draw_bot = ray->y_bot;
	if (*draw_top < 0)
		*draw_top = 0;
	if (*draw_bot > sH)
		*draw_bot = sH;
	return (*draw_top < *draw_bot);
}

/* melange le pixel du decalque (alpha du png) avec ce qui est deja dans le frame_buffer */
static void	blend_decal_pixel(Uint32 *fb, t_RGB c, int light_level)
{
	t_RGB	behind;
	float	a;

	if (c.alphaValue == 0)
		return ;
	if (c.alphaValue < 255)
	{
		behind.r = (*fb >> 16) & 0xFF;
		behind.g = (*fb >> 8) & 0xFF;
		behind.b = (*fb) & 0xFF;
		a = c.alphaValue / 255.0f;
		c.r = c.r * a + behind.r * (1.0f - a);
		c.g = c.g * a + behind.g * (1.0f - a);
		c.b = c.b * a + behind.b * (1.0f - a);
	}
	*fb = write_color(c.r, c.g, c.b, light_level);
}

static void	draw_decal(t_game *game, t_ray *ray, int x, t_sector *sector, t_decal *decal)
{
	float	u_world;
	float	y_top_f, y_bot_f;
	int		draw_top, draw_bot;
	int		tex_x, tex_y;
	float	vh, vh_step, plane_z;
	Uint32	*fb;

	if (decal->width <= 0.0f || decal->height <= 0.0f)
		return ;
	plane_z = get_plane_z(sector->floor_plane, decal->pos.x, decal->pos.y);
	u_world = ray->u * game->map->walls[ray->wall_idx].length;
	if (u_world < decal->u_offset || u_world > decal->u_offset + decal->width)
		return ;
	y_bot_f = game->screenSize[1] / 2 - ((decal->z_bottom + plane_z - game->ply->z) / ray->perp_dist) * ray->focal + game->ply->pitch;
	y_top_f = game->screenSize[1] / 2 - ((decal->z_bottom + plane_z + decal->height - game->ply->z) / ray->perp_dist) * ray->focal + game->ply->pitch;
	if (!clamp_decal_band(ray, game->screenSize[1], y_top_f, y_bot_f, &draw_top, &draw_bot))
		return ;
	tex_x = (int)((u_world - decal->u_offset) / decal->width * decal->texture.w);
	tex_x = SDL_clamp(tex_x, 0, decal->texture.w - 1);
	vh_step = (float)decal->texture.h / (y_bot_f - y_top_f);
	vh = ((float)draw_top - y_top_f) * vh_step;
	fb = &game->frame_buffer[draw_top * game->screenSize[0] + x];
	for (int y = draw_top; y < draw_bot; y++)
	{
		tex_y = SDL_clamp((int)vh, 0, decal->texture.h - 1);
		vh += vh_step;
		blend_decal_pixel(fb, decal->texture.colors[tex_y * decal->texture.w + tex_x], sector->light_level);
		fb += game->screenSize[0];
	}
}

/* dessine tous les decalques colles sur le mur touche par ce rayon */
void	draw_decals(t_game *game, t_ray *ray, int x, t_sector *sector)
{
	t_map	*map;
	int		i;

	map = game->map;
	i = 0;
	while (i < map->num_decals)
	{
		if (map->decals[i].wall_idx == ray->wall_idx)
			draw_decal(game, ray, x, sector, &map->decals[i]);
		i++;
	}
}
