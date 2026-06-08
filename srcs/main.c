/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/06/08 12:45:32 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI/GUI.h"
#include "menus/menus.h"
#include "Game.h"
#include "Events.h"
#include "parser/PNG.h"
#include "Colors.h"
#include "multiplayer/server.h"
#include "multiplayer/client.h"

int main(void)
{
	t_game *game;

	game = init_game();
	if (!game)
		return (1);

	game->ply->pos.x = 4.0f;
	game->ply->pos.y = 4.0f;
	game->ply->dir.x = 0.0f;
	game->ply->dir.y = 1.0f;
	game->ply->sector = 0;
	ft_bzero(&game->ply->keys, sizeof(t_keys));

	game->mapSize[0] = 24;
	game->mapSize[1] = 24;

	t_vect2 pos;
	pos.x = game->ply->pos.x + 1; pos.y = game->ply->pos.y;
	default_enemy(game, pos, "assets/png/entities/shooter.png", "assets/png/entities/shooter_attack.png", 400, 600);

	pthread_create(&game->serverThread, NULL, create_server, game);

	while (1)
	{
		// Uint64 start = SDL_GetPerformanceCounter();
		SDL_RenderClear(game->window->renderPTR);
		events_handler(game);
		draw_current_menu(game);
		display_notif(game->window, &game->window->menus.notif.notif_buf);

		// display_buttons(game->window->buttonList, game->window->renderPTR);
		// Creation du renderer (de la frame)
		// SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);
		// draw_player(game->window->renderPTR, game, 20, rgb);

		// display_hud(game);
		display_fps(game);

		pickup_flash(game);
		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
		// display_fps_periodic(start);
		send_corresponding_datas_to_server(game);
		handle_server_response(game, &game->clientConnection);
	}

	exit_game(game, NULL);
	return 0;
}
