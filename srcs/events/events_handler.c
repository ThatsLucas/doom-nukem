/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:53:23 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/06 13:39:52 by lle-duc          ###   ########.fr       */
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
static void key_handler(t_game *game, SDL_KeyboardEvent key, SDL_Event *event)
{
	t_ply *ply;

	if (key.keysym.sym == 27)
		exit_game(game, NULL);
		
	if (key.keysym.sym == SDLK_p && event->type == SDL_KEYDOWN && game->window->menus.current == 0) //pause
	{
		game->is_paused ^= 1;
		SDL_SetRelativeMouseMode(!game->is_paused);
	}
	
	if (key.keysym.sym == 1073741906 || key.keysym.sym == 1073741905)
		ply_pitch(game, game->ply, key);
	if (key.keysym.sym == SDLK_e)
		interactions(game);

	ply = game->ply;
	ply->keys.w = (event->type == SDL_KEYDOWN && key.keysym.sym == game->settings.move_forward) ? 1 : ply->keys.w;
	ply->keys.a = (event->type == SDL_KEYDOWN && key.keysym.sym == game->settings.move_left) ? 1 : ply->keys.a;
	ply->keys.s = (event->type == SDL_KEYDOWN && key.keysym.sym == game->settings.move_backward) ? 1 : ply->keys.s;
	ply->keys.d = (event->type == SDL_KEYDOWN && key.keysym.sym == game->settings.move_right) ? 1 : ply->keys.d;
	ply->keys.left = (event->type == SDL_KEYDOWN && key.keysym.sym == 1073741904) ? 1 : ply->keys.left;
	ply->keys.right = (event->type == SDL_KEYDOWN && key.keysym.sym == 1073741903) ? 1 : ply->keys.right;
	ply->keys.space = (event->type == SDL_KEYDOWN && key.keysym.sym == SDLK_SPACE) ? 1 : ply->keys.space;

	ply->keys.w = (event->type == SDL_KEYUP && key.keysym.sym == game->settings.move_forward) ? 0 : ply->keys.w;
	ply->keys.a = (event->type == SDL_KEYUP && key.keysym.sym == game->settings.move_left) ? 0 : ply->keys.a;
	ply->keys.s = (event->type == SDL_KEYUP && key.keysym.sym == game->settings.move_backward) ? 0 : ply->keys.s;
	ply->keys.d = (event->type == SDL_KEYUP && key.keysym.sym == game->settings.move_right) ? 0 : ply->keys.d;
	ply->keys.left = (event->type == SDL_KEYUP && key.keysym.sym == 1073741904) ? 0 : ply->keys.left;
	ply->keys.right = (event->type == SDL_KEYUP && key.keysym.sym == 1073741903) ? 0 : ply->keys.right;
	ply->keys.space = (event->type == SDL_KEYUP && key.keysym.sym == SDLK_SPACE) ? 0 : ply->keys.space;

	printf("Key space = %d\n", ply->keys.space);
	if (key.keysym.sym == SDLK_f && event->type == SDL_KEYDOWN)
		activate_flashlight(game);

	if (key.keysym.sym == SDLK_LSHIFT && event->type == SDL_KEYDOWN)
		ply->physic.is_running = 1;

	if (key.keysym.sym == SDLK_LSHIFT && event->type == SDL_KEYUP)
		ply->physic.is_running = 0;

	if (key.keysym.sym == SDLK_LCTRL && event->type == SDL_KEYDOWN)
		player_crouch(ply);

	if (key.keysym.sym == SDLK_LCTRL && event->type == SDL_KEYUP)
		player_crouch(ply);
}

void events_handler(t_game *game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEWHEEL:
			// const char *weapon_names[] = {"Fists", "Pistol", "Shotgun", "Rocket Launcher"};
			// printf("Changement d'arme !\nAncienne arme: %s\n", weapon_names[game->ply->current_weap_index]);
			if (game->window->menus.current == 0)
				handle_mousewheel(game, &event.wheel);
			if (game->window->menus.current == 2)
				handle_settings_scroll_mouse_wheel(game, &game->window->menus.settings, &event.wheel);
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
			handle_key_control_selected(game, event.key.keysym.sym);
			key_handler(game, event.key, &event);
			// printf("Key Released: %d\n", event.key.keysym.sym);
			break;

		case SDL_MOUSEBUTTONDOWN:				
			if (event.button.button == SDL_BUTTON_LEFT && game->window->menus.current == 0 && !game->is_paused)
				player_shoot(game);
			else
			{
				if (game->window->menus.current == 2)
					handle_settings_click(game, &game->window->menus.settings, &event.motion, 1);
				check_button_pressed(game, game->window->buttonList);
			}
			break;
		case SDL_MOUSEMOTION:
			if (game->window->menus.current == 2)
				handle_settings_click(game, &game->window->menus.settings, &event.motion, 0);
			if (game->window->menus.current == 0)
				mouse_moves(event.motion.xrel, event.motion.yrel, game);
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.state == SDL_RELEASED)
			{
				if (game->window->menus.current == 2)
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

	return;
}
