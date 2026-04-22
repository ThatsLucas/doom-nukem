/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:23:50 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/22 14:48:26 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

void	display_grid(t_game *game)
{
	int	offset_x, offset_y;

	offset_x = game->window->w * 0.75 / game->mapSize[0];
	offset_y = game->window->h / game->mapSize[1];
	SDL_SetRenderDrawColor(game->window->renderPTR, 189, 17, 17, SDL_ALPHA_OPAQUE);

	for (int i = offset_x; i < game->window->w * 0.75; i += offset_x)
		SDL_RenderDrawLine(game->window->renderPTR, i, 0, i, game->window->h);

	for (int i = offset_y; i < game->window->h; i += offset_y)
		SDL_RenderDrawLine(game->window->renderPTR, 0, i, game->window->w * 0.75, i);

	return ;
}
