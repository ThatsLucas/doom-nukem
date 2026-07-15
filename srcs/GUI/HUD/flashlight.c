/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:41:20 by edurance          #+#    #+#             */
/*   Updated: 2026/07/15 17:46:22 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"
#include "Game.h"

static void	flash_pixels(t_game *game, int cx, int cy, float intensity)
{
	int	sw = game->screenSize[0];
	int	sh = game->screenSize[1];
	int	radius = 400;
	int	radius2 = radius * radius;
	int	xmin = SDL_clamp(cx - radius, 0, sw - 1);
	int	xmax = SDL_clamp(cx + radius, 0, sw - 1);
	int	ymin = SDL_clamp(cy - radius, 0, sh - 1);
	int	ymax = SDL_clamp(cy + radius, 0, sh - 1);

	for (int y = ymin; y <= ymax; y++)
	{
		for (int x = xmin; x <= xmax; x++)
		{
			int	dx = x - cx;
			int	dy = y - cy;
			int	dist2 = dx * dx + dy * dy;

			if (dist2 <= radius2)
			{
				float	dist_ratio = (float)dist2 / (float)radius2;
				float	falloff = 1.0f - dist_ratio;
				float	factor = 1.0f + (intensity - 1.0f) * falloff;

				Uint32	*px = &game->frame_buffer[y * sw + x];
				int	r = (*px >> 16) & 0xFF;
				int	g = (*px >> 8) & 0xFF;
				int	b = *px & 0xFF;

				r = SDL_min(255, (int)(r * factor));
				g = SDL_min(255, (int)(g * factor));
				b = SDL_min(255, (int)(b * factor));

				*px = (r << 16) | (g << 8) | b;
			}
		}
	}
}

void	flashlight_use(t_game *game)
{
	float	intensity = 0.0f;
	for (int i = 0; i < game->ply->inventory.tool_count; i++)
	{
		t_tool	flash = game->ply->inventory.tools[i];
		if (flash.type == TOOL_FLASHLIGHT && flash.using == 1)
		{
			if (flash.data.battery > 3)
				intensity = 4.5f;
			else
				intensity = 2.5f;
			printf("used\n");
			int	cx = game->screenSize[0] / 2;
			int	cy = game->screenSize[1] / 2;
			flash_pixels(game, cx, cy, intensity);
			return ;
		}
	}
}
