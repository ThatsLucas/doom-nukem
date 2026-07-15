/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_separators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:52:27 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/23 16:19:08 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/*	Affiche les séparateurs dans les propriétés	*/
void	display_separators(t_game *game)
{
	SDL_Rect	line;

	SDL_SetRenderDrawColor(game->window->renderPTR, 132, 132, 132, SDL_ALPHA_OPAQUE);
	line.x = 1455;
	line.w = 450;
	line.h = 3;
	line.y = 124;
	to_responsive(game->window, &line);
	SDL_RenderFillRect(game->window->renderPTR, &line);
	line.y = (277 * game->window->h) / 1080;
	SDL_RenderFillRect(game->window->renderPTR, &line);
	line.y = (417 * game->window->h) / 1080;
	SDL_RenderFillRect(game->window->renderPTR, &line);
	line.y = (994 * game->window->h) / 1080;
	SDL_RenderFillRect(game->window->renderPTR, &line);

	return ;
}
