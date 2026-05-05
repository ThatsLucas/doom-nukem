/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 11:28:42 by edurance          #+#    #+#             */
/*   Updated: 2026/04/19 11:29:07 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Game.h"

/* Function to display the crossair as a cross with a gap in the middle */
void	display_crosshair(t_game *game, int x, int y, int size, int gap, t_RGB rgb)
{
	int				status = 0;
	SDL_Renderer	*render = game->window->renderPTR;

	SDL_SetRenderDrawColor(render, rgb.r, rgb.g, rgb.b, rgb.alphaValue);

	status += SDL_RenderDrawLine(render, x - size, y, x - gap, y);
	status += SDL_RenderDrawLine(render, x + gap, y, x + size, y);
	status += SDL_RenderDrawLine(render, x, y - size, x, y - gap);
	status += SDL_RenderDrawLine(render, x, y + gap, x, y + size);
}
