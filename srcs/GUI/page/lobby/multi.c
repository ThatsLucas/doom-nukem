/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:42:03 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/26 15:37:11 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

static void draw_texts(t_game *game, t_lobby *menu)
{
    draw_texture(1920 / 2 - (menu->texts[11].w / 2), 50, menu->texts[11].w, menu->texts[11].h, game->window, menu->texts[11].texture);
}
void draw_lobby_multiplayer_menu(t_game *game)
{
    // SDL_Renderer *renderer = game->window->renderPTR;
    t_WIN *win = game->window;
    t_lobby *menu = &win->menus.lobby;

    game->window->menus.current = 4;

    draw_texture(0, 0, 1920, 1080, win, menu->multi_background.texture);
    draw_texture(20, 20, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture(400, 850, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture((1920 / 2 - (win->menus.main.button.w / 5 / 2)), 850, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture(1520 - win->menus.main.button.w / 5, 850, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);

    draw_texture(400, (1000 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture((1920 / 2 - (win->menus.main.button.w / 5 / 2)), (1000 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture(1520 - win->menus.main.button.w / 5, (1000 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);

    int breathFrame = (SDL_GetTicks() / 1600) % 3;
    draw_texture(1920 / 2 - (1024 / 8 / 2), 500, 1024 / 8, 1536 / 8, win, menu->playerImgs[breathFrame].texture);
    draw_texture(1920 / 2 - (1024 / 8 / 2) - 150, 500, 1024 / 8, 1536 / 8, win, menu->playerImgs[(breathFrame + 1) % 3].texture);
    draw_texture(1920 / 2 - (1024 / 8 / 2) + 150, 500, 1024 / 8, 1536 / 8, win, menu->playerImgs[(breathFrame + 2) % 3].texture);
    draw_texture(1920 / 2 - (1024 / 8 / 2) - 300, 500, 1024 / 8, 1536 / 8, win, menu->playerImgs[(breathFrame + 3) % 3].texture);

    draw_texts(game, menu);
    display_buttons(game->window->buttonList, game, 4);
}
