/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/08 13:01:11 by aabouyaz         ###   ########.fr       */
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

	// t_coordinates coords;
	// coords.x = 200;
	// coords.y = 200;
	// coords.w = 150;
	// coords.h = 80;

	// t_RGB buttoncolor;
	// buttoncolor.r = 0;
	// buttoncolor.g = 60;
	// buttoncolor.b = 255;
	// buttoncolor.alphaValue = 255;

	// t_RGB hoverColor;
	// hoverColor.r = 90;
	// hoverColor.g = 60;
	// hoverColor.b = 150;
	// hoverColor.alphaValue = 255;

	// create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);
	// coords.x = 200;
	// coords.y = 300;
	// create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);
	// coords.x = 200;
	// coords.y = 400;
	// create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);

	game->ply->pos.x = 3;
	game->ply->pos.y = 2;
	game->ply->dir.x = 1.0f;
	game->ply->dir.y = 0.0f;
	ft_bzero(&game->ply->keys, sizeof(t_keys));

	game->mapSize[0] = 7;	game->mapSize[1] = 4;
	t_vect2 p[4];

	p[0].x = 2.0f;	p[0].y = 0.5f;
	p[1].x = 4.7f;	p[1].y = 1.2f;
	p[2].x = 3.2f;	p[2].y = 2.7f;
	p[3].x = 0.7f;	p[3].y = 2.4f;

	while (1)
	{
		events_handler(game);

		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 120, 52, 50, 255);
		SDL_RenderClear(game->window->renderPTR);

		display_buttons(game->window->buttonList, game->window->renderPTR);
		// Creation du renderer (de la frame)
		// SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);

		SDL_SetRenderDrawColor(game->window->renderPTR, 0, 0, 255, 255);
		draw_wall(game, p[0], p[1]);
		draw_wall(game, p[1], p[2]);
		draw_wall(game, p[2], p[3]);
		draw_wall(game, p[3], p[0]);

		draw_player(game->window->renderPTR, game, 20, rgb);

		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
	}

	exit_game(game, NULL);

	return 0;
}
