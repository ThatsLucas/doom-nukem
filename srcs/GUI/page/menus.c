/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 23:32:07 by lucas             #+#    #+#             */
/*   Updated: 2026/10/28 10:56:10 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"
#include "multiplayer/shared.h"

/* Affiche les éléments du jeu en cours. */
static void draw_in_game(t_game *game)
{
	apply_constant_forces_to_player(game->ply);
	send_rays(game);        // murs/sols/toits -> frame_buffer + z_buffer
	render_entities(game);  // sprites dans le frame_buffer, caches par le z_buffer
	update_item(game);
	render_items(game);     // idem pour les objets au sol
	update_projectiles(game);
	render_projectiles(game); // roquettes et explosions
	SDL_UpdateTexture(game->frame, NULL, game->frame_buffer, game->screenSize[0] * sizeof(Uint32));
	SDL_RenderCopy(game->window->renderPTR, game->frame, NULL, NULL);
	if (game->clientConnection.is_connected)
		render_multiplayer_players(game);
	pickup_flash(game);
	display_hud(game);
	draw_pause_menu(game);
	check_elevator(game->map);
	if (game->current_level < 3 && is_on_level_exit(game))
	{
		load_level(game, game->current_level + 1);
		return ;
	}
	if (game->ply->hp <= 0)
		draw_game_over_menu(game);
}

/* Affiche la page active. */
void draw_current_menu(t_game *game)
{
	switch (game->window->menus.current)
	{
	case 0:
		play_music(&game->sounds, game->sounds.ingame_music);
		draw_in_game(game);
		break;
	case 1:
		play_music(&game->sounds, game->sounds.menu_music);
		draw_main_menu(game);
		break;
	case 2:
		play_music(&game->sounds, game->sounds.menu_music);
		draw_settings_menu(game);
		break;
	case 3:
		play_music(&game->sounds, game->sounds.menu_music);
		draw_lobby_menu(game);
		break;
	case 4:
		play_music(&game->sounds, game->sounds.menu_music);
		draw_lobby_multiplayer_menu(game);
		break;
	case 5:
		draw_cinematic_one(game);
		break;
	case 6:
		draw_cinematic_two(game);
		break;
	case 7:
		draw_cinematic_three(game);
		break;
	default:
		break;
	}
}
