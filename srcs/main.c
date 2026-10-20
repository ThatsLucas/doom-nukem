/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/05 11:57:22 by edurance         ###   ########.fr       */
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
#include "inventory/Items.h"

/* TEST: charge un niveau et saute direct en jeu (pas de menu, pas de cinematique) */
static void load_start_level(t_game *game)
{
	free_map(game->map);
	game->map = load_map("level1", game, 0);
	if (!game->map)
		exit_game(game, "TEST: failed to load level1");
	game->current_level = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	game->window->menus.current = 1;
}

/* One frame of the editor */
static void editor_frame(t_game *game)
{
	editor_events(game);
	display_editor(game);
	SDL_RenderPresent(game->window->renderPTR);
}

/* One frame of the game / menus, then sync with the server */
static void game_frame(t_game *game)
{
	events_handler(game);
	draw_current_menu(game);
	display_notif(game->window, &game->window->menus.notif.notif_buf);
	display_fps(game);

	// affichage du renderer sur la page
	SDL_RenderPresent(game->window->renderPTR);
	send_corresponding_datas_to_server(game);
	if (game->settings.multiplayer_enabled)
		handle_server_response(game, &game->clientConnection);
}

int main(void)
{
	t_game *game;

	game = init_game();
	if (!game)
		return (1);

	ft_bzero(&game->ply->keys, sizeof(t_keys));
	load_start_level(game);

	pthread_create(&game->serverThread, NULL, create_server, game);

	while (1)
	{
		SDL_RenderClear(game->window->renderPTR);
		if (game->window->menus.current == -1)
			editor_frame(game);
		else
			game_frame(game);
	}

	exit_game(game, NULL);
	return 0;
}
