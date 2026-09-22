/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/09/22 13:00:45 by edurance         ###   ########.fr       */
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

static void	spawn_test_items(t_game *game)
{
	t_vect2	p;
	t_vect2	it;

	p = game->ply->pos;

	it = (t_vect2){p.x + 2.0f, p.y - 2.0f};
	create_item_heal(game, it, 25);
	it = (t_vect2){p.x + 2.0f, p.y};
	create_item_fuel(game, it, 30);
	it = (t_vect2){p.x + 2.0f, p.y + 2.0f};
	create_item_battery(game, it, 30);

	it = (t_vect2){p.x + 4.0f, p.y - 2.0f};
	create_item_pistol(game, it, 12);
	it = (t_vect2){p.x + 4.0f, p.y};
	create_item_shotgun(game, it, 8);
	it = (t_vect2){p.x + 4.0f, p.y + 2.0f};
	create_item_rocket_launcher(game, it, 3);

	it = (t_vect2){p.x + 6.0f, p.y - 2.0f};
	create_item_flashlight(game, it);
	it = (t_vect2){p.x + 6.0f, p.y};
	create_item_key(game, it, 0);
	it = (t_vect2){p.x + 6.0f, p.y + 2.0f};
	create_item_jetpack(game, it);
}

int main(void)
{
	t_game *game;

	game = init_game();
	if (!game)
		return (1);

	ft_bzero(&game->ply->keys, sizeof(t_keys));

	/* charge un niveau et saute direct en jeu (pas de menu, pas de cinematique) */
	free_map(game->map);
	game->map = load_map("level1", game, 0);
	if (!game->map)
		exit_game(game, "TEST: failed to load level1");
	game->current_level = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	game->window->menus.current = 0;

	spawn_test_items(game);

	pthread_create(&game->serverThread, NULL, create_server, game);

	while (1)
	{
		// Uint64 start = SDL_GetPerformanceCounter();
		SDL_RenderClear(game->window->renderPTR);

		if (game->window->menus.current == -1)
		{
			editor_events(game);
			display_editor(game);
			SDL_RenderPresent(game->window->renderPTR);
			continue ;
		}
		events_handler(game);
		draw_current_menu(game);
		display_notif(game->window, &game->window->menus.notif.notif_buf);

		// display_buttons(game->window->buttonList, game->window->renderPTR);
		// Creation du renderer (de la frame)
		// SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);
		// draw_player(game->window->renderPTR, game, 20, rgb);

		// display_hud(game);
		display_fps(game);

		// pickup_flash(game);
		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
		send_corresponding_datas_to_server(game);
		handle_server_response(game, &game->clientConnection);
	}

	exit_game(game, NULL);
	return 0;
}