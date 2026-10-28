/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:11:22 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/28 10:53:53 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Window.h"
#include "menus/menus.h"

/* Initialise le texte du game over. */
void    init_game_over_texts(t_game *game)
{
    t_game_over *menu = &game->window->menus.game_over;

    menu->texts[0].size = 150;
    menu->texts[0].color = (SDL_Color){221, 21, 0, 255};
    create_text(&menu->texts[0], game->window->renderPTR, game->languages->game_over, DNFONT);
}

/* Affiche l'écran de game over pendant GAME_OVER_DURATION secondes. */
void    draw_game_over_menu(t_game *game)
{
    t_WIN *win = game->window;
    t_game_over *game_over_menu = &win->menus.game_over;
    t_font *text = &game_over_menu->texts[0];
    
    if (!game->is_game_over)
    {
        game->is_game_over = 1;
        game_over_menu->game_over_begin_time = SDL_GetTicks64();
    }
    
    Uint64 Curtime = SDL_GetTicks64();

    if (Curtime - game_over_menu->game_over_begin_time > GAME_OVER_DURATION * 1000)
    {
        game->is_game_over = 0;
        if (game->clientConnection.is_connected)
            close_connection(game);
        game->window->menus.current = 1;
    }
    
    SDL_Rect coords = {0, 0, 1920, 1080};
    to_responsive(win, &coords);

    t_RGB light_grey = {217, 217, 217, 127};
    create_rectangle(win->renderPTR, coords, light_grey);

    draw_texture(1920 / 2 - text->w / 2, 1080 / 2 - text->h / 2, text->w, text->h, win, text->texture);
}
