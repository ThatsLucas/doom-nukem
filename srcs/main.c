/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/16 23:25:50 by aabouyaz         ###   ########.fr       */
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

	game->ply->pos.x = 3.0f;
	game->ply->pos.y = 2.0f;
	game->ply->dir.x = 0.0f;
	game->ply->dir.y = 1.0f;
	ft_bzero(&game->ply->keys, sizeof(t_keys));

	game->mapSize[0] = 12;	game->mapSize[1] = 8;

	create_notif(&game->window->PopupPtr.notif_buf, "Le lutin est aux arrivants, envoie le lassot mokhtar, je peux pas je suis au mitar ! QUOOOOOI T fou d'etre au mitard en big 2026!!!!", 5, 35);

	create_notif(&game->window->PopupPtr.notif_buf, "CECI EST UNE GROSSE NOTIF !", 2, 80);

	create_notif(&game->window->PopupPtr.notif_buf, "UN BOSS EST APPARU DANS LA SALLE DES BOSS", 5, 55);

	create_notif(&game->window->PopupPtr.notif_buf, "BANGER CE JEU", 5, 90);
	while (1)
	{
		events_handler(game);
		
		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 51, 20, 7, 255);
		SDL_RenderClear(game->window->renderPTR);

		// draw_main_menu(&game->window->MainMenu, game);
		send_rays(game);
		SDL_UpdateTexture(game->frame, NULL, game->frame_buffer, game->screenSize[0] * sizeof(Uint32));
		SDL_RenderCopy(game->window->renderPTR, game->frame, NULL, NULL);

		// display_notif(game->window, &game->window->PopupPtr.notif_buf);

		// display_buttons(game->window->buttonList, game->window->renderPTR);		
		// Creation du renderer (de la frame)
		// SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);
		// draw_player(game->window->renderPTR, game->ply, 20, rgb);

		display_fps(game);
		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
	}

	exit_game(game, NULL);
	return 0;
}