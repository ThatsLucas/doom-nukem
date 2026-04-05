/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/05 17:14:47 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI.h"
#include "Game.h"
#include "Events.h"

int main(void)
{
	t_game	*game;

	game = init_game();
	if (!game)
		return (1);

	t_RGB rgb;
	rgb.r = 51;
	rgb.g = 153;
	rgb.b = 255;
	rgb.alphaValue = 255;

	game->ply->pos_x = 500;
	game->ply->pos_y = 500;
	game->ply->dir_x = 0.0f;
	game->ply->dir_y = -1.0f;

	while (1)
	{
		events_handler(game);

		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 255, 0, 0, 255);
		SDL_RenderClear(game->window->renderPTR);

		// Creation du renderer (de la frame)
		create_rectangle(game->window->renderPTR, 50, 50, 200, 200, rgb);
		create_rectangle(game->window->renderPTR, 650, 50, 200, 200, rgb);
		create_rectangle(game->window->renderPTR, 900/2 - 25, 225, 50, 50, rgb);
		create_rectangle(game->window->renderPTR, 50, 400, 800, 50, rgb);
		SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);

		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
	}

	exit_game(game, NULL);
	return 0;
}
