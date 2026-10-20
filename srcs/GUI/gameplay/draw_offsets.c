/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_offsets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:17:46 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/12 16:55:12 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI/GUI.h"

/* Dessine la partie supérieure de la surface. */
static void	draw_top(int ny_top, t_ray *ray, t_tex *tex, int x, t_game *game, t_sector *sector)
{
	int		tex_x, tex_y;
	float	u_world, vh, vh_step;
	t_RGB	c;
	t_wall	*w;
	int		sW			= game->screenSize[0], sH = game->screenSize[1];
	int		step_top	= SDL_clamp(ray->y_top, 0, sH - 1);
	int		step_ny_top	= SDL_clamp(ny_top, 0, sH - 1);

	w			= &game->map->walls[ray->wall_idx];
	u_world		= ray->u * w->length;
	if (w->tex_upper >= 0 && ny_top - ray->y_top > 1)
	{
		tex_x		= (int)(u_world * tex->w) % tex->w;
		vh_step		= (float)tex->h / (float)(ray->y_wall_bot - ray->y_wall_top);
		vh			= (float)(step_top - ray->y_wall_top) * vh_step;
		Uint32 *fb	= &game->frame_buffer[step_top * sW + x];
		float *zb	= &game->z_buffer[step_top * sW + x];
		for (int y = step_top; y < step_ny_top; y++)
		{
			tex_y	= (int)vh % tex->h;
			vh		+= vh_step;
			c		= tex->colors[tex_y * tex->w + tex_x];
			*fb		= write_color(x, y, game, c, sector->light_level);
			*zb		= ray->perp_dist;
			fb		+= sW;
			zb		+= sW;
		}
	}
	return ;
}

/* Dessine la partie inférieure de la surface. */
static void	draw_bot(int ny_bot, t_ray *ray, t_tex *tex, int x, t_game *game, t_sector *sector)
{
	int		tex_x, tex_y;
	float	u_world, vh, vh_step;
	t_RGB	c;
	t_wall	*w;
	int		sW			= game->screenSize[0], sH = game->screenSize[1];
	int		step_ny_bot	= SDL_clamp(ny_bot, 0, sH - 1);
	int		step_bot	= SDL_clamp(ray->y_bot, 0, sH - 1);

	w			= &game->map->walls[ray->wall_idx];
	u_world		= ray->u * w->length;
	if (w->tex_lower >= 0 && ray->y_bot - ny_bot > 1)
	{
		tex_x = (int)(u_world * tex->w) % tex->w;
		vh_step		= (float)tex->h / (float)(ray->y_wall_bot - ray->y_wall_top);
		vh			= (float)(step_ny_bot - ray->y_wall_top) * vh_step;
		Uint32 *fb	= &game->frame_buffer[step_ny_bot * sW + x];
		float *zb	= &game->z_buffer[step_ny_bot * sW + x];
		for (int y = step_ny_bot; y < step_bot; y++)
		{
			tex_y	= (int)vh % tex->h;
			vh		+= vh_step;
			c		= tex->colors[tex_y * tex->w + tex_x];
			*fb		= write_color(x, y, game, c, sector->light_level);
			*zb		= ray->perp_dist;
			fb		+= sW;
			zb		+= sW;
		}
	}
	return ;
}

/* Dessine les parties haute et basse d’un mur de portail. */
void	draw_offsets(t_ray *ray, t_game *game, int ny_top, int ny_bot, int x, t_sector *sector)
{
	t_wall	*w;

	w			= &game->map->walls[ray->wall_idx];

	ny_top		= SDL_clamp(ny_top, ray->y_top, ray->y_bot);
	ny_bot		= SDL_clamp(ny_bot, ray->y_top, ray->y_bot);

	draw_top(ny_top, ray, &game->map->textures[w->tex_upper], x, game, sector);
	draw_bot(ny_bot, ray, &game->map->textures[w->tex_lower], x, game, sector);

	ray->y_top	= ny_top;
	ray->y_bot	= ny_bot;

	return ;
}
