/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root- <root-@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:39:45 by root-             #+#    #+#             */
/*   Updated: 2026/04/09 17:39:49 by root-            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI.h"
#include "Game.h"
#include "Events.h"
#include "parser/PNG.h"

int main(void)
{

	process_png("assets/png/doom_nukem.png");

	t_game	*game;

	game = init_game();
	if (!game)
		return (1);

	t_RGB rgb;
	rgb.r = 51;
	rgb.g = 153;
	rgb.b = 255;
	rgb.alphaValue = 255;

	t_coordinates coords;
	coords.x = 200;
	coords.y = 200;
	coords.w = 150;
	coords.h = 80;

	t_RGB buttoncolor;
	buttoncolor.r = 0;
	buttoncolor.g = 60;
	buttoncolor.b = 255;
	buttoncolor.alphaValue = 255;

	t_RGB hoverColor;
	hoverColor.r = 90;
	hoverColor.g = 60;
	hoverColor.b = 150;
	hoverColor.alphaValue = 255;

	create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);
	coords.x = 200;
	coords.y = 300;
	create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);
	coords.x = 200;
	coords.y = 400;
	create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);


	game->ply->pos_x = 500;
	game->ply->pos_y = 500;
	game->ply->dir_x = 1.0f;
	game->ply->dir_y = 0.0f;
	ft_bzero(&game->ply->keys, sizeof(t_keys));

	while (1)
	{
		events_handler(game);

		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 255, 0, 0, 255);
		SDL_RenderClear(game->window->renderPTR);

		display_buttons(game->window->buttonList, game->window->renderPTR);		
		// Creation du renderer (de la frame)
		// SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);
		draw_player(game->window->renderPTR, game->ply, 20, rgb);

		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
	}

	exit_game(game, NULL);

	return 0;
}