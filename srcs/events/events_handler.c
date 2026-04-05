/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:53:23 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/05 17:23:04 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"

/*
	27 = Escape
	119 = W
	97 = A
	115 = S
	100 = D
	1073741903 = RIGHT
	1073741904 = LEFT
*/
static void	key_handler(t_game *game, SDL_KeyboardEvent key)
{
	if (key.keysym.sym == 27)
		exit_game(game, NULL);
	ply_movements(key.keysym.sym, game->ply, game);
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
			key_handler(game, event.key);
			printf("Key Pressed: %d\n", event.key.keysym.sym);
			break;

		case SDL_KEYUP:
			printf("Key Released: %d\n", event.key.keysym.sym);
			break;
		}
	}
}
