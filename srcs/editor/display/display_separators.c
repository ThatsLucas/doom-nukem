/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_separators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:52:27 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 12:57:12 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

void	display_separators(t_game *game)
{
	SDL_Rect	line;

	SDL_SetRenderDrawColor(game->window->renderPTR, 132, 132, 132, SDL_ALPHA_OPAQUE);
	line.x = game->editor->plan.size.w + 15;
	line.w = 450;
	line.h = 3;
	line.y = 102;
	to_responsive(game->window, &line);
	SDL_RenderFillRect(game->window->renderPTR, &line);
	line.y = 277;
	to_responsive(game->window, &line);
	SDL_RenderFillRect(game->window->renderPTR, &line);
	line.y = 417;
	to_responsive(game->window, &line);
	SDL_RenderFillRect(game->window->renderPTR, &line);
	line.y = 994;
	to_responsive(game->window, &line);
	SDL_RenderFillRect(game->window->renderPTR, &line);

	return ;
}
