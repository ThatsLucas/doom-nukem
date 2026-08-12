/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:24:01 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/12 17:25:33 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"

static t_tool	*get_flashlight(t_game *game)
{
	for (int i = 0; i < game->ply->inventory.tool_count; i++)
	{
		t_tool	flash = game->ply->inventory.tools[i];
		if (flash.type == TOOL_FLASHLIGHT)
			return (&game->ply->inventory.tools[i]);
	}

	return (NULL);
}

/*
	Renvoie une couleur par rapport au facteur de lumiere 
	le bit shift de 8 est une division par 256 et pas 255 => résultat imparfait mais optimisé
*/
Uint32  write_color(int x, int y, t_game *game, t_RGB c, int sect_light)
{
	static t_tool	*flashlight = NULL;

	if (!flashlight)
		flashlight = get_flashlight(game);
	if (!flashlight)
		return (0);

	int		radius = 400;
	int		radius2 = radius * radius;
	int		dx = x - (game->screenSize[0] / 2);
	int		dy = y - (game->screenSize[1] / 2);
	int		dist2 = dx * dx + dy * dy;
	float	intensity = 0.0f;

	if (flashlight->using && dist2 <= radius2)
	{
		if (flashlight->data.battery > 3)
			intensity = 2.0f;
		else if (flashlight->data.battery <= 0)
			flashlight->using = 0;
		else
			intensity = 1.5f;
		float	dist_ratio = (float)dist2 / (float)radius2;
		float	falloff = 1.0f - dist_ratio;
		float	factor = 1.0f + (intensity - 1.0f) * falloff;

		c.r = SDL_min(255, (int)(c.r * factor));
		c.g = SDL_min(255, (int)(c.g * factor));
		c.b = SDL_min(255, (int)(c.b * factor));

		return ((c.r << 16) | (c.g << 8) | c.b);
	}

	c.r = (c.r * sect_light) >> 8;
	c.g = (c.g * sect_light) >> 8;
	c.b = (c.b * sect_light) >> 8;
	return ((c.r << 16) | (c.g << 8) | c.b);
}
