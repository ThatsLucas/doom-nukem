/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:05:35 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/15 13:33:23 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI.h"

/* affiche un mur */
void	draw_wall(t_game *game, t_ray *ray, int x, t_sector *sector)
{
	int		draw_top = (ray->y_wall_top > ray->y_top) ? ray->y_wall_top : ray->y_top;
	int		draw_bot = (ray->y_wall_bot < ray->y_bot) ? ray->y_wall_bot : ray->y_bot;
	t_wall	*w;
	float	u_world, wall_len, v;
	int		tex_x, tex_y;
	t_RGB	c;

	w			= &game->map->walls[ray->wall_idx];
	wall_len	= dist_vect(game->map->vertices[w->v1], game->map->vertices[w->v2]);
	u_world		= ray->u * wall_len;
	tex_x		= (int)(u_world * game->map->surface[w->tex_mid]->w) % game->map->surface[w->tex_mid]->w;
	for (int y = draw_top; y < draw_bot; y++)
	{
		v		= (float)(y - ray->y_wall_top) / (float)(ray->y_wall_bot - ray->y_wall_top);
		tex_y	= (int)(v * game->map->surface[w->tex_mid]->h) % game->map->surface[w->tex_mid]->h;
		c		= game->map->text_colors[w->tex_mid][tex_y * game->map->surface[w->tex_mid]->w + tex_x];
		game->frame_buffer[y * game->screenSize[0] + x] = write_color(c.r, c.g, c.b, sector->light_level);
	}
}
