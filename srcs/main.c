/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:39:45 by root-             #+#    #+#             */
/*   Updated: 2026/04/14 00:04:46 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI.h"
#include "menus/menus.h"
#include "Game.h"
#include "Events.h"
#include "parser/PNG.h"

int main(void)
{
	t_game	*game;

	game = init_game();
	if (!game)
		return (1);

	game->ply->pos_x = 500;
	game->ply->pos_y = 500;
	game->ply->dir_x = 1.0f;
	game->ply->dir_y = 0.0f;
	ft_bzero(&game->ply->keys, sizeof(t_keys));

	t_notif_buf *notifbuf = NULL;
	create_notif(&notifbuf, "Ceci est un test", 5);
	int wait = 1000;
	while (1)
	{
		events_handler(game);
		
		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 51, 20, 7, 255);
		SDL_RenderClear(game->window->renderPTR);

		draw_main_menu(&game->window->MainMenu, game);
		if (wait > 2500)
			display_notif(game->window, &notifbuf);
		wait++;
		printf("wait = %d\n", wait);
		// display_buttons(game->window->buttonList, game->window->renderPTR);		
		// Creation du renderer (de la frame)
		// SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);
		// draw_player(game->window->renderPTR, game->ply, 20, rgb);

		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
	}

	exit_game(game, NULL);
	return 0;
}