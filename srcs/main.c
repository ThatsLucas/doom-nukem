/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/12 12:43:04 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI.h"
#include "Game.h"
#include "Events.h"
#include "parser/PNG.h"

void editor(t_game *game)
{
	if (game->status == 0)
		game->status = -1;
	else if (game->status == -1)
	{
		game->status = 1;
		game->bspTree = bsp(game, game->walls);
		SDL_ShowCursor(SDL_DISABLE);
	}
	return ;
}

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
	coords.x = 100;
	coords.y = 50;
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

	create_button(&game->window->buttonList, &editor, coords, buttoncolor, hoverColor);
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

	game->mapSize[0] = 20;	game->mapSize[1] = 15;
	Uint32 bg = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888), 120, 52, 50);

	while (1)
	{
		events_handler(game);

		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 120, 52, 50, 255);
		SDL_RenderClear(game->window->renderPTR);

		// Creation du renderer (de la frame)
		// SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);

		if (game->status > 0)
		{
			for (int i = 0; i < game->screenSize[0] * game->screenSize[1]; i++)
				game->frame_buffer[i] = bg;
			SDL_SetRenderDrawColor(game->window->renderPTR, 0, 0, 255, 255);
			send_rays(game, rgb);
			SDL_UpdateTexture(game->frame, NULL, game->frame_buffer, game->screenSize[0] * sizeof(Uint32));
			SDL_RenderCopy(game->window->renderPTR, game->frame, NULL, NULL);
			draw_walls(game, rgb);
			draw_player(game->window->renderPTR, game, 20, rgb);

		}
		else if (game->status == -1)
			draw_walls(game, rgb);

		if (game->status == 0 || game->status == -1)	//editor ou mainMenu
			display_buttons(game->window->buttonList, game->window->renderPTR);

		display_fps(game);
		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
	}

	exit_game(game, NULL);

	return 0;
}
