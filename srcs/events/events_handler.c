/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:53:23 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/21 14:41:56 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"
#include "GUI/GUI.h"
#include "Game.h"

/*
	27 = Escape
	119 = W
	97 = A
	115 = S
	100 = D
	1073741903 = RIGHT
	1073741904 = LEFT
	1073741906 = UP
	1073741905 = DOWN
	8 = BackSpace
*/
static void	key_handler(t_game *game, SDL_KeyboardEvent key, SDL_Event *event)
{
	t_ply	*ply;

	if (key.keysym.sym == 27)
		exit_game(game, NULL);
	if (key.keysym.sym == 1073741906 || key.keysym.sym == 1073741905)
		ply_pitch(game, game->ply, key);
	ply = game->ply;
	ply->keys.w = (event->type == SDL_KEYDOWN && key.keysym.sym == 119) ? 1 : ply->keys.w;
	ply->keys.a = (event->type == SDL_KEYDOWN && key.keysym.sym == 97) ? 1 : ply->keys.a;
	ply->keys.s = (event->type == SDL_KEYDOWN && key.keysym.sym == 115) ? 1 : ply->keys.s;
	ply->keys.d = (event->type == SDL_KEYDOWN && key.keysym.sym == 100) ? 1 : ply->keys.d;
	ply->keys.left = (event->type == SDL_KEYDOWN && key.keysym.sym == 1073741904) ? 1 : ply->keys.left;
	ply->keys.right = (event->type == SDL_KEYDOWN && key.keysym.sym == 1073741903) ? 1 : ply->keys.right;

	ply->keys.w = (event->type == SDL_KEYUP && key.keysym.sym == 119) ? 0 : ply->keys.w;
	ply->keys.a = (event->type == SDL_KEYUP && key.keysym.sym == 97) ? 0 : ply->keys.a;
	ply->keys.s = (event->type == SDL_KEYUP && key.keysym.sym == 115) ? 0 : ply->keys.s;
	ply->keys.d = (event->type == SDL_KEYUP && key.keysym.sym == 100) ? 0 : ply->keys.d;
	ply->keys.left = (event->type == SDL_KEYUP && key.keysym.sym == 1073741904) ? 0 : ply->keys.left;
	ply->keys.right = (event->type == SDL_KEYUP && key.keysym.sym == 1073741903) ? 0 : ply->keys.right;
}

void	events_handler(t_game *game)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
			case SDL_MOUSEWHEEL:
				// const char *weapon_names[] = {"Fists", "Pistol", "Shotgun", "Rocket Launcher"};
				// printf("Changement d'arme !\nAncienne arme: %s\n", weapon_names[game->ply->current_weap_index]);
				handle_mousewheel(game, &event.wheel);
				// printf("Nouvelle arme: %s\n", weapon_names[game->ply->current_weap_index]);
				break;

			case SDL_QUIT:
				exit_game(game, NULL);
				break;
			
			case SDL_KEYDOWN:
				key_handler(game, event.key, &event);
				break;
				// printf("Key Pressed: %d\n", event.key.keysym.sym);
			
			case SDL_KEYUP:
				key_handler(game, event.key, &event);
				// printf("Key Released: %d\n", event.key.keysym.sym);
				break;
			
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT && game->window->menus.current == 0) 
					player_shoot(game);
				else
				{
					check_button_pressed(game, game->window->buttonList);
					handle_settings_click(game, &game->window->menus.settings, &event.motion, 1);
				}
				break;
			case SDL_MOUSEMOTION:
				if (game->window->menus.current == 2)
					handle_settings_click(game, &game->window->menus.settings, &event.motion, 0);
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.state == SDL_RELEASED)
				{
					handle_settings_released(&game->window->menus.settings);
				}
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					game->window->w = event.window.data1;
					game->window->h = event.window.data2;
				}
		}
	}

	ply_directions(game->ply);
	ply_movements(game->ply, game);

	return ;
}
