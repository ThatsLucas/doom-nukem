/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/05 13:29:16 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "menus/menus.h"
#include "Game.h"
#include "Events.h"
#include "parser/PNG.h"
#include "Editor.h"


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

	game->window->menus.current = -1;
	SDL_StartTextInput();

	while (1)
	{
		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 51, 20, 7, 255);
		SDL_RenderClear(game->window->renderPTR);

		if (game->window->menus.current == -1)
		{
			editor_events(game);
			display_editor(game);
			SDL_RenderPresent(game->window->renderPTR);
			continue;
		}

		display_fps(game);

	}

	exit_game(game, NULL);
	return 0;
}
