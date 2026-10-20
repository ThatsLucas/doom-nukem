/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_zbuf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 10:00:00 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 16:31:22 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"
#include "GUI/GUI.h"

/* Dessine un sprite pixel par pixel en respectant le z-buffer. */
void	draw_sprite_zbuf(t_game *game, t_tex *tex, SDL_Rect d, float depth, int light)
{
	int		sW = game->screenSize[0], sH = game->screenSize[1];
	int		x0 = SDL_max(d.x, 0), x1 = SDL_min(d.x + d.w, sW);
	int		y0 = SDL_max(d.y, 0), y1 = SDL_min(d.y + d.h, sH);
	int		tex_x, idx;
	t_RGB	c;

	for (int x = x0; x < x1; x++)
	{
		tex_x = (int)((long)(x - d.x) * tex->w / d.w);
		for (int y = y0; y < y1; y++)
		{
			idx = y * sW + x;
			if (depth >= game->z_buffer[idx])
				continue ;
			c = tex->colors[(int)((long)(y - d.y) * tex->h / d.h) * tex->w + tex_x];
			if (c.alphaValue < 128)
				continue ;
			game->frame_buffer[idx] = write_color(x, y, game, c, light);
			game->z_buffer[idx] = depth;
		}
	}
}
