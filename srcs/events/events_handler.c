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

static void on_mouse_button_down(t_game *game, SDL_Event *event)
{
	if (event->button.button == SDL_BUTTON_LEFT && game->window->menus.current == 0 && !game->is_paused)
		player_shoot(game);
	else
	{
		if (game->window->menus.current == 2)
			handle_settings_click(game, &game->window->menus.settings, &event->motion, 1);
		check_button_pressed(game, game->window->buttonList);
	}
}

static void on_mouse_motion(t_game *game, SDL_Event *event)
{
	if (game->window->menus.current == 2)
		handle_settings_click(game, &game->window->menus.settings, &event->motion, 0);
	if (game->window->menus.current == 0 && SDL_GetRelativeMouseMode()) // pas de rotation/warp si la souris n'est pas capturee
		mouse_moves(event->motion.xrel, event->motion.yrel, game);
}

static void on_mouse_wheel(t_game *game, SDL_Event *event)
{
	if (game->window->menus.current == 0)
		handle_mousewheel(game, &event->wheel);
	if (game->window->menus.current == 2)
		handle_settings_scroll_mouse_wheel(game, &game->window->menus.settings, &event->wheel);
}

static void on_window_event(t_game *game, SDL_Event *event)
{
	if (event->window.event == SDL_WINDOWEVENT_RESIZED)
	{
		game->window->w = event->window.data1;
		game->window->h = event->window.data2;
	}
	handle_focus(game, event->window.event);
}

static void dispatch_event(t_game *game, SDL_Event *event)
{
	if (event->type == SDL_MOUSEWHEEL)
		on_mouse_wheel(game, event);
	else if (event->type == SDL_QUIT)
		exit_game(game, NULL);
	else if (event->type == SDL_KEYDOWN)
		key_handler(game, event->key, event);
	else if (event->type == SDL_KEYUP)
	{
		handle_key_control_selected(game, event->key.keysym.sym);
		key_handler(game, event->key, event);
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN)
		on_mouse_button_down(game, event);
	else if (event->type == SDL_MOUSEMOTION)
		on_mouse_motion(game, event);
	else if (event->type == SDL_MOUSEBUTTONUP)
	{
		if (event->button.state == SDL_RELEASED && game->window->menus.current == 2)
			handle_settings_released(&game->window->menus.settings);
	}
	else if (event->type == SDL_WINDOWEVENT)
		on_window_event(game, event);
}

void events_handler(t_game *game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
		dispatch_event(game, &event);

	update_mouse_capture(game);
	ply_directions(game->ply);
	ply_movements(game->ply, game);

	return;
}
