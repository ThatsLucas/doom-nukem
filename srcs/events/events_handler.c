/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:53:23 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/12 16:00:06 by edurance         ###   ########.fr       */
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
	if (event->type == SDL_KEYUP && key.keysym.sym == SDLK_e)
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

	if (key.keysym.sym == SDLK_f && event->type == SDL_KEYDOWN)
		activate_flashlight(game);

	if (key.keysym.sym == SDLK_LSHIFT)
		player_run(ply, event->type == SDL_KEYDOWN);

	if (key.keysym.sym == SDLK_LCTRL)
		player_crouch(ply);
		
	if (ply->keys.space && (game->window->menus.current == 5 || game->window->menus.current == 6 || game->window->menus.current == 7))
		game->window->menus.current = 0;
}

/*
	Alt-tab : on relache les touches, les KEYUP sont perdus quand la fenetre
	n'a plus le focus (sinon le joueur continue d'avancer tout seul)
*/
static void handle_focus(t_game *game, Uint8 window_event)
{
	if (window_event == SDL_WINDOWEVENT_FOCUS_LOST)
		ft_bzero(&game->ply->keys, sizeof(t_keys));
}

/*
	Capture la souris seulement en jeu/cinematique, hors pause, et si la fenetre
	a le focus. Verifie a chaque frame : si SDL refuse au retour d'un alt-tab
	(souris pas encore dans la fenetre), on reessaie a la frame suivante
*/
static void update_mouse_capture(t_game *game)
{
	int			menu = game->window->menus.current;
	Uint32		flags = SDL_GetWindowFlags(game->window->winPTR);
	SDL_bool	want;

	want = (menu == 0 || (menu >= 5 && menu <= 7)) && !game->is_paused
		&& (flags & SDL_WINDOW_INPUT_FOCUS);
	if (SDL_GetRelativeMouseMode() != want)
		SDL_SetRelativeMouseMode(want);
}

void events_handler(t_game *game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEWHEEL:
			if (game->window->menus.current == 0)
				handle_mousewheel(game, &event.wheel);
			if (game->window->menus.current == 2)
				handle_settings_scroll_mouse_wheel(game, &game->window->menus.settings, &event.wheel);
			break;

		case SDL_QUIT:
			exit_game(game, NULL);
			break;

		case SDL_KEYDOWN:
			key_handler(game, event.key, &event);
			break;

		case SDL_KEYUP:
			handle_key_control_selected(game, event.key.keysym.sym);
			key_handler(game, event.key, &event);
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
			if (game->window->menus.current == 0 && SDL_GetRelativeMouseMode()) // pas de rotation/warp si la souris n'est pas capturee
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
			handle_focus(game, event.window.event);
			break;
		}
	}

	update_mouse_capture(game);
	ply_directions(game->ply);
	ply_movements(game->ply, game);

	return;
}
