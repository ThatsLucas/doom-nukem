/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_slopes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 11:36:33 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/17 12:28:32 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Affiche les propriétés des pentes. */
void	display_slopes(t_game *game)
{
	SDL_Rect	box;

	draw_prop_text(game, "floor", 1549, 494);
	draw_prop_text(game, "ceiling", 1744, 494);

	draw_prop_text(game, "ceil_intensity", 1494, 577);
	draw_prop_text(game, "floor_intensity", 1494, 662);

	box.h = 35; box.w = 80; box.x = 1639; box.y = 495;
	to_responsive(game->window, &box);
	SDL_SetRenderDrawColor(game->window->renderPTR, 255, 255, 188, 255);
	SDL_RenderFillRect(game->window->renderPTR, &box);
	SDL_SetRenderDrawColor(game->window->renderPTR, 0, 0, 0, 255);
	SDL_RenderDrawRect(game->window->renderPTR, &box);

	box.h = 27; box.w = 36; box.y = 499;
	if (game->editor->properties.slope_fc)
		box.x = 1679;
	else
		box.x = 1643;
	to_responsive(game->window, &box);
	SDL_RenderFillRect(game->window->renderPTR, &box);

	return ;
}
