/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_offsets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:17:46 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/15 13:33:21 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI.h"

static void	draw_top(int ny_top, t_ray *ray, SDL_Surface *S, int x, t_game *game, t_sector *sector)
{
	int		tex_x, tex_y;
	float	u_world, v, wall_len;
	t_RGB	c;
	t_wall	*w;
	int		sW			= game->screenSize[0], sH = game->screenSize[1];
	int		step_top	= SDL_clamp(ray->y_top, 0, sH - 1);
	int		step_ny_top	= SDL_clamp(ny_top, 0, sH - 1);

	w			= &game->map->walls[ray->wall_idx];
	wall_len	= dist_vect(game->map->vertices[w->v1], game->map->vertices[w->v2]);
	u_world		= ray->u * wall_len;
	if (w->tex_upper >= 0 && ny_top - ray->y_top > 1)
	{
		tex_x = (int)(u_world * S->w) % S->w;
		for (int y = step_top; y < step_ny_top; y++)
		{
			v		= (float)(y - ray->y_wall_top) / (float)(ray->y_wall_bot - ray->y_wall_top);
			tex_y	= (int)(v * S->h) % S->h;
			if (tex_y < 0) tex_y = 0;
			if (tex_y >= S->h) tex_y = S->h - 1;
			c		= game->map->text_colors[w->tex_upper][tex_y * S->w + tex_x];
			game->frame_buffer[y * sW + x] = write_color(c.r, c.g, c.b, sector->light_level);
		}
	}
	return ;
}

static void	draw_bot(int ny_bot, t_ray *ray, SDL_Surface *S, int x, t_game *game, t_sector *sector)
{
	int		tex_x, tex_y;
	float	u_world, v, wall_len;
	t_RGB	c;
	t_wall	*w;
	int		sW			= game->screenSize[0], sH = game->screenSize[1];
	int		step_ny_bot	= SDL_clamp(ny_bot, 0, sH - 1);
	int		step_bot	= SDL_clamp(ray->y_bot, 0, sH - 1);

	w			= &game->map->walls[ray->wall_idx];
	wall_len	= dist_vect(game->map->vertices[w->v1], game->map->vertices[w->v2]);
	u_world		= ray->u * wall_len;
	if (w->tex_lower >= 0 && ray->y_bot - ny_bot > 1)
	{
		tex_x = (int)(u_world * S->w) % S->w;
		for (int y = step_ny_bot; y < step_bot; y++)
		{
			v		= (float)(y - ray->y_wall_top) / (float)(ray->y_wall_bot - ray->y_wall_top);
			tex_y	= (int)(v * S->h) % S->h;
			if (tex_y < 0) tex_y = 0;
			if (tex_y >= S->h) tex_y = S->h - 1;
			c		= game->map->text_colors[w->tex_lower][tex_y * S->w + tex_x];
			game->frame_buffer[y * sW + x] = write_color(c.r, c.g, c.b, sector->light_level);
		}
	}
	return ;
}

/* dessine le decalage entre le portail et le plafond + le portail et le sol */
void	draw_offsets(t_ray *ray, t_game *game, int ny_top, int ny_bot, int x, t_sector *sector)
{
	t_wall	*w;

	w			= &game->map->walls[ray->wall_idx];
	draw_top(ny_top, ray, game->map->surface[w->tex_upper], x, game, sector);
	draw_bot(ny_bot, ray, game->map->surface[w->tex_lower], x, game, sector);

	ny_top		= SDL_clamp(ny_top, ray->y_top, ray->y_bot);
	ny_bot		= SDL_clamp(ny_bot, ray->y_top, ray->y_bot);
	ray->y_top	= ny_top;
	ray->y_bot	= ny_bot;

	return ;
}
