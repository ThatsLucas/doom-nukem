/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/14 12:38:10 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI.h"
#include "Game.h"
#include "Events.h"
#include "parser/PNG.h"



int main(void)
{
	// process_png("assets/png/doom_nukem.png");

	t_game	*game;

	game = init_game();
	if (!game)
		return (1);

	t_RGB rgb;
	rgb.r = 51;
	rgb.g = 153;
	rgb.b = 255;
	rgb.alphaValue = 255;

	game->ply->pos.x = 3.0f;
	game->ply->pos.y = 2.0f;
	game->ply->dir.x = 0.0f;
	game->ply->dir.y = 1.0f;
	ft_bzero(&game->ply->keys, sizeof(t_keys));

	game->mapSize[0] = 12;	game->mapSize[1] = 8;
	Uint32 bg = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888), 120, 52, 50);

	while (1)
	{
		events_handler(game);
		// game->ply->z = get_plane_z(game->map->sectors[game->ply->sector].floor_plane, game->ply->pos.x, game->ply->pos.y) + EYES_HEIGTH;

		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 120, 52, 50, 255);
		SDL_RenderClear(game->window->renderPTR);

		// Creation du renderer (de la frame)
		for (int i = 0; i < game->screenSize[0] * game->screenSize[1]; i++)
			game->frame_buffer[i] = bg;
		SDL_SetRenderDrawColor(game->window->renderPTR, 0, 0, 255, 255);
		send_rays(game);
		SDL_UpdateTexture(game->frame, NULL, game->frame_buffer, game->screenSize[0] * sizeof(Uint32));
		SDL_RenderCopy(game->window->renderPTR, game->frame, NULL, NULL);

		draw_player(game->window->renderPTR, game, 20, rgb);

		display_fps(game);
		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
	}

	exit_game(game, NULL);

	return 0;
}
