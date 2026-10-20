/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 12:45:26 by lle-duc           #+#    #+#             */
/*   Updated: 2026/07/06 14:54:26 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Window.h"
#include "menus/menus.h"

static void draw_game_menu(t_game *game)
{
    game->is_paused = 0;
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

static void go_main_menu(t_game *game)
{
    game->is_paused = 0;
    SDL_SetRelativeMouseMode(SDL_FALSE);
    if (game->clientConnection.is_connected)
    {
        close_connection(game);
        game->clientConnection.is_connected = 0;
    }
    game->window->menus.current = 1;
}

static void init_pause_buttons(t_WIN *win, t_pause *menu)
{
    t_main_menu *MainMenu = &win->menus.main;
    int button_offset = 150;
    t_RGB color = {0, 255, 0, 0};
    SDL_Rect coords = {1920 / 2 - (MainMenu->button.w / 5) / 2, 450, MainMenu->button.w / 5, MainMenu->button.h / 5};

    create_button(&win->buttonList, &draw_game_menu, coords, color, color, &menu->texts[1], &menu->texts[2], 0);
    coords.y += button_offset;
    create_button(&win->buttonList, &draw_settings_menu, coords, color, color, &MainMenu->btn_two_text, &MainMenu->btn_two_text_hover, 0);
    coords.y += button_offset + 5;
    create_button(&win->buttonList, &go_main_menu, coords, color, color, &menu->texts[3], &menu->texts[4], 0);
}

void init_pause_texts(void *gameStruct)
{
    t_game *game = (t_game *)gameStruct;
    t_WIN *win = game->window;
    t_languages *lang = game->languages;
    SDL_Renderer *renderer = win->renderPTR;
    t_pause *menu = &win->menus.pause;

    menu->texts[0].size = 120;
    menu->texts[0].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[1].size = 60;
    menu->texts[1].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[1].textHOffset = -10;
    menu->texts[2].size = 60;
    menu->texts[2].color = (SDL_Color){221, 21, 0, 255};
    menu->texts[2].textHOffset = -5;
    menu->texts[3].size = 60;
    menu->texts[3].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[3].textHOffset = -5;
    menu->texts[4].size = 60;
    menu->texts[4].color = (SDL_Color){221, 21, 0, 255};
    menu->texts[4].textHOffset = -5;

    create_text(&menu->texts[0], renderer, lang->pause, DNFONT);
    create_text(&menu->texts[1], renderer, lang->resume, DNFONTOUTLINED);
    create_text(&menu->texts[2], renderer, lang->resume, DNFONT);
    create_text(&menu->texts[3], renderer, lang->exit, DNFONTOUTLINED);
    create_text(&menu->texts[4], renderer, lang->exit, DNFONT);

    init_pause_buttons(win, menu);
}

void draw_pause_menu(t_game *game)
{
    t_WIN *win = game->window;
    t_pause *pause = &win->menus.pause;
    t_main_menu *menu = &win->menus.main;
    
    if (!game->is_paused)
        return;
    SDL_Rect coords = {0, 0, 1920, 1080};
    to_responsive(win, &coords);

    t_RGB black = {0, 0, 0, 200};
    create_rectangle(win->renderPTR, coords, black);
 
    draw_texture(1920 / 2 - (pause->texts[0].w / 2), 150, pause->texts[0].w, pause->texts[0].h, win, pause->texts[0].texture);

    // //button
    int button_offset = 150;
    int button_pos_h = 450;
    
    draw_texture(1920/2 - (menu->button.w / 5) / 2, button_pos_h, menu->button.w / 5, menu->button.h / 5, win, menu->button.texture);
    button_pos_h += button_offset;
    draw_texture(1920/2 - (menu->button.w / 5) / 2, button_pos_h, menu->button.w / 5, menu->button.h / 5, win, menu->button.texture);
    button_pos_h += button_offset;
    draw_texture(1920/2 - (menu->button.w / 5) / 2, button_pos_h, menu->button.w / 5, menu->button.h / 5, win, menu->button.texture);

    
    display_buttons(game->window->buttonList, game, 0);
}