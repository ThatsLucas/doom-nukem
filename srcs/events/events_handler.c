/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:53:23 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/06 14:52:05 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"
#include "GUI.h"

/*
	27 = Escape
	119 = W
	97 = A
	115 = S
	100 = D
	1073741903 = RIGHT
	1073741904 = LEFT
*/
static void	key_handler(t_game *game, SDL_KeyboardEvent key, SDL_Event *event)
{
	t_ply	*ply;

	if (key.keysym.sym == 27)
		exit_game(game, NULL);

	ply = game->ply;
	ply->keys.w = (event->type == SDL_KEYDOWN && key.keysym.sym == 119) ? 1 : ply->keys.w;
	ply->keys.a = (event->type == SDL_KEYDOWN && key.keysym.sym == 97) ? 1 : ply->keys.a;
	ply->keys.s = (event->type == SDL_KEYDOWN && key.keysym.sym == 115) ? 1 : ply->keys.s;
	ply->keys.d = (event->type == SDL_KEYDOWN && key.keysym.sym == 100) ? 1 : ply->keys.d;

	ply->keys.w = (event->type == SDL_KEYUP && key.keysym.sym == 119) ? 0 : ply->keys.w;
	ply->keys.a = (event->type == SDL_KEYUP && key.keysym.sym == 97) ? 0 : ply->keys.a;
	ply->keys.s = (event->type == SDL_KEYUP && key.keysym.sym == 115) ? 0 : ply->keys.s;
	ply->keys.d = (event->type == SDL_KEYUP && key.keysym.sym == 100) ? 0 : ply->keys.d;


	// printf("============================\n");
	// printf("W ====> %d\n", ply->keys.w);
	// printf("A ====> %d\n", ply->keys.a);
	// printf("S ====> %d\n", ply->keys.s);
	// printf("D ====> %d\n", ply->keys.d);
	// printf("============================\n");

	ply_movements(game->ply, game);
	ply_directions(key.keysym.sym, game->ply);
}

void	events_handler(t_game *game)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
			case SDL_MOUSEMOTION:
				// printf("Mouse pos = %d, %d\n", event.motion.x, event.motion.y);
				break;

			case SDL_QUIT:
				exit_game(game, NULL);
				break;

			case SDL_KEYDOWN:
				key_handler(game, event.key, &event);
				// printf("Key Pressed: %d\n", event.key.keysym.sym);
				break;

			case SDL_KEYUP:
				key_handler(game, event.key, &event);
				// printf("Key Released: %d\n", event.key.keysym.sym);
				break;
			
			case SDL_MOUSEBUTTONDOWN:
				check_button_pressed(game->window, game->window->buttonList);
				break;
		}

	}
}
