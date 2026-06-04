/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 11:28:42 by edurance          #+#    #+#             */
/*   Updated: 2026/06/04 16:06:40 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

/* Function to display the crossair as a cross with a gap in the middle */
void	display_crosshair(t_game *game, int x, int y, int size, int gap)
{
	int				status = 0;
	SDL_Renderer	*render = game->window->renderPTR;
	t_RGB			rgb;

	if (!game->ply->crosshair_target)
		rgb = (t_RGB){255, 255, 255, 255};
	else if (game->ply->crosshair_target->type == ENTITY_ENEMY)
		rgb = (t_RGB){255, 0, 0, 255};
	else if (game->ply->crosshair_target->type == ENTITY_PNJ)
		rgb = (t_RGB){0, 255, 0, 255};

	SDL_SetRenderDrawColor(render, rgb.r, rgb.g, rgb.b, rgb.alphaValue);

	status += SDL_RenderDrawLine(render, x - size, y, x - gap, y);
	status += SDL_RenderDrawLine(render, x + gap, y, x + size, y);
	status += SDL_RenderDrawLine(render, x, y - size, x, y - gap);
	status += SDL_RenderDrawLine(render, x, y + gap, x, y + size);
}
