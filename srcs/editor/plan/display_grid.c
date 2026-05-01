/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:23:50 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/01 17:08:57 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

void	display_grid(t_game *game)
{
	float	offset_x, offset_y;

	offset_x = (float)game->editor->plan.w / game->mapSize[0];
	offset_y = (float)game->editor->plan.h / game->mapSize[1];
	SDL_SetRenderDrawColor(game->window->renderPTR, 189, 17, 17, SDL_ALPHA_OPAQUE);

	for (float i = offset_x; i < game->editor->plan.w; i += offset_x)
		SDL_RenderDrawLine(game->window->renderPTR, i, 0, i, game->window->h);

	for (float i = offset_y; i < game->editor->plan.h - 1; i += offset_y)
		SDL_RenderDrawLine(game->window->renderPTR, 0, i, game->editor->plan.w, i);

	return ;
}
