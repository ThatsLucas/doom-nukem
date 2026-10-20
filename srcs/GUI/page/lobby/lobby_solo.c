/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby_solo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:57:44 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/20 16:33:14 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"
#include "multiplayer/client.h"

/* Affiche les textes du salon solo. */
static void draw_texts(t_game *game, t_lobby *menu)
{
    draw_texture(1920 / 2 - (menu->texts[0].w / 2), 150, menu->texts[0].w, menu->texts[0].h, game->window, menu->texts[0].texture);
}

/* Affiche le salon solo. */
void draw_lobby_menu(t_game *game)
{
    // SDL_Renderer *renderer = game->window->renderPTR;
    t_WIN *win = game->window;
    t_lobby *menu = &win->menus.lobby;

    game->window->menus.current = 3;

    draw_texture(0, 0, 1920, 1080, win, menu->background.texture);
    draw_texture(20, 20, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture(400, (1080 / 2 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture((1920 / 2 - (win->menus.main.button.w / 5 / 2)), (1080 / 2 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture(1520 - win->menus.main.button.w / 5, (1080 / 2 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture((1920 / 2 - (win->menus.main.button.w / 5 / 2)), (1000 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);

    int breathFrame = (SDL_GetTicks() / 1600) % 3;
    draw_texture(1920 / 2 - (1024 / 4 / 2), 580, 1024 / 4, 1536 / 4, win, menu->playerImgs[breathFrame].texture);

    draw_texts(game, menu);
    display_buttons(game->window->buttonList, game, 3);
}
