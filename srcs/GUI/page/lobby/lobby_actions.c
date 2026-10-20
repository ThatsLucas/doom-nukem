/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:07:30 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:07:30 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"
#include "multiplayer/client.h"

/* Charge le niveau demandé. */
void load_level(t_game *game, int level)
{
    static char *names[3] = {"level1", "level2", "level3"};

    if (level < 1 || level > 3)
        return;
    SDL_Color white = {255, 255, 255, 255};
    t_font font;
    font.color = white;
    font.size = 120;
	t_WIN	*win = game->window;

	create_text(&font, win->renderPTR, game->languages->loading, DNFONT);
	SDL_Rect text_dest = {(1920 - font.w) / 2, (1080 - font.h) / 2, font.w, font.h};
	to_responsive(win, &text_dest);
	SDL_RenderCopy(win->renderPTR, font.texture, NULL, &text_dest);
	SDL_RenderPresent(win->renderPTR);

	game->current_level = level;
	free_map(game->map);
	game->map = load_map(names[level - 1], game, 0);
	// le chargement bloque la boucle, on repart de maintenant pour pas timeout
	game->clientConnection.last_update = SDL_GetTicks64();
	if (!game->map)
		return ;
    SDL_SetRelativeMouseMode(SDL_TRUE);
    game->clientConnection.state = 3;
    game->window->menus.current = 4 + level;
    game->window->menus.cinematic.cinematatic_duration = CINEMATIC_ONE_DURATION;
}

/* Vérifie si le niveau peut être lancé. */
static int can_start_level(t_game *game)
{
    if (game->settings.multiplayer_enabled && !game->settings.is_host)
    {
        create_notif(&game->window->menus.notif.notif_buf, "Only the host can do that!", 5, 70);
        return (0);
    }
    return (1);
}

/* Lance le niveau 1. */
void start_level_1(t_game *game)
{
    if (can_start_level(game))
        load_level(game, 1);
}

/* Lance le niveau 2. */
void start_level_2(t_game *game)
{
    if (can_start_level(game))
        load_level(game, 2);
}

/* Lance le niveau 3. */
void start_level_3(t_game *game)
{
    if (can_start_level(game))
        load_level(game, 3);
}

/* Quitte le salon pour le menu principal. */
void lobby_to_main_menu(t_game *game)
{
    if (game->settings.multiplayer_enabled)
        close_connection(game);
    game->window->menus.current = 1;
}

/* Ouvre le salon multijoueur. */
void lobby_to_multi_lobby(t_game *game)
{
    if (game->settings.multiplayer_enabled)
        close_connection(game);
    game->window->menus.current = 4;
}

/* Ouvre le salon solo. */
void lobby_to_solo_lobby(t_game *game)
{
    if (game->settings.multiplayer_enabled)
        close_connection(game);
    game->window->menus.current = 3;
}
