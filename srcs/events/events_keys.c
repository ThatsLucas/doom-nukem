/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:21:33 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 16:30:54 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"
#include "GUI/GUI.h"
#include "Game.h"

/* Met à jour l’état des touches de déplacement. */
static void update_movement_keys(t_game *game, SDL_KeyboardEvent key, SDL_Event *event)
{
	t_ply *ply;

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
}

/* Gère l’appui ou le relâchement d’une touche. */
void key_handler(t_game *game, SDL_KeyboardEvent key, SDL_Event *event)
{
	t_ply *ply;

	if (key.keysym.sym == 27)
		exit_game(game, NULL);
	if (player_is_dead(game))
		return ;
		
	if (key.keysym.sym == SDLK_p && event->type == SDL_KEYDOWN && game->window->menus.current == 0) //pause
	{
		game->is_paused ^= 1;
		SDL_SetRelativeMouseMode(!game->is_paused);
	}
	
	if (key.keysym.sym == 1073741906 || key.keysym.sym == 1073741905)
		ply_pitch(game, game->ply, key);
	if (event->type == SDL_KEYUP && key.keysym.sym == SDLK_e)
		interactions(game);

	update_movement_keys(game, key, event);
	ply = game->ply;

	if (key.keysym.sym == SDLK_f && event->type == SDL_KEYDOWN)
		activate_flashlight(game);

	if (key.keysym.sym == SDLK_LSHIFT)
		player_run(ply, event->type == SDL_KEYDOWN);

	if (key.keysym.sym == SDLK_LCTRL)
		player_crouch(ply);
		
	if (ply->keys.space && (game->window->menus.current == 5 || game->window->menus.current == 6 || game->window->menus.current == 7))
		game->window->menus.current = 0;
}
