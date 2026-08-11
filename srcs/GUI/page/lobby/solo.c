/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:57:44 by lle-duc           #+#    #+#             */
/*   Updated: 2026/08/11 14:20:41 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"
#include "multiplayer/client.h"
// #include "../../../includes/GUI.h"

void start_level_1(t_game *game)
{
    game->current_level = 1;
	free_map(game->map);
	game->map = load_map("level1", game);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    game->clientConnection.state = 3;
    game->window->menus.current = 5;
    game->window->menus.cinematic.cinematatic_duration = CINEMATIC_ONE_DURATION;
}

void start_level_2(t_game *game)
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    game->current_level = 2;
    game->clientConnection.state = 3;
    game->window->menus.current = 6;
    game->window->menus.cinematic.cinematatic_duration = CINEMATIC_ONE_DURATION;
}

void start_level_3(t_game *game)
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    game->current_level = 3;
    game->clientConnection.state = 3;
    game->window->menus.current = 7;
    game->window->menus.cinematic.cinematatic_duration = CINEMATIC_ONE_DURATION;
}

static void change_menu_to_main_menu(t_game *game)
{
    game->window->menus.current = 1;
}

static void change_menu_to_multi_lobby(t_game *game)
{
    game->window->menus.current = 4;
}

static void change_menu_to_solo_lobby(t_game *game)
{
    game->window->menus.current = 3;
}

static void *init_texts(void *gameStruct)
{
    t_game *game = (t_game *)gameStruct;
    t_WIN *win = game->window;
    t_languages *lang = game->languages;
    SDL_Renderer *renderer = win->renderPTR;
    t_lobby *menu = &win->menus.lobby;

    menu->texts[0].size = 200;
    menu->texts[0].color = (SDL_Color){255, 255, 255, 255};
    create_text(&menu->texts[0], renderer, lang->lobby_solo, DNFONT);

    menu->texts[1].color = (SDL_Color){221, 21, 0, 255};
    menu->texts[1].size = 60;
    menu->texts[1].textHOffset = -10;
    create_text(&menu->texts[1], renderer, lang->main_menu, DNFONT);

    menu->texts[2].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[2].size = 60;
    menu->texts[2].textHOffset = -10;
    create_text(&menu->texts[2], renderer, lang->main_menu, DNFONTOUTLINED);

    menu->texts[3].color = (SDL_Color){221, 21, 0, 255};
    menu->texts[3].size = 60;
    menu->texts[3].textHOffset = -10;
    create_text(&menu->texts[3], renderer, lang->level_one, DNFONT);

    menu->texts[4].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[4].size = 60;
    menu->texts[4].textHOffset = -10;
    create_text(&menu->texts[4], renderer, lang->level_one, DNFONTOUTLINED);

    menu->texts[5].color = (SDL_Color){221, 21, 0, 255};
    menu->texts[5].size = 60;
    menu->texts[5].textHOffset = -10;
    create_text(&menu->texts[5], renderer, lang->level_two, DNFONT);

    menu->texts[6].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[6].size = 60;
    menu->texts[6].textHOffset = -10;
    create_text(&menu->texts[6], renderer, lang->level_two, DNFONTOUTLINED);

    menu->texts[7].color = (SDL_Color){221, 21, 0, 255};
    menu->texts[7].size = 60;
    menu->texts[7].textHOffset = -10;
    create_text(&menu->texts[7], renderer, lang->level_three, DNFONT);

    menu->texts[8].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[8].size = 60;
    menu->texts[8].textHOffset = -10;
    create_text(&menu->texts[8], renderer, lang->level_three, DNFONTOUTLINED);

    menu->texts[9].color = (SDL_Color){221, 21, 0, 255};
    menu->texts[9].size = 60;
    menu->texts[9].textHOffset = -10;
    create_text(&menu->texts[9], renderer, lang->multiplayer, DNFONT);

    menu->texts[10].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[10].size = 60;
    menu->texts[10].textHOffset = -10;
    create_text(&menu->texts[10], renderer, lang->multiplayer, DNFONTOUTLINED);

    menu->texts[11].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[11].size = 200;
    menu->texts[11].textHOffset = -10;
    create_text(&menu->texts[11], renderer, lang->lobby_multi, DNFONT);

    menu->texts[12].color = (SDL_Color){221, 21, 0, 255};
    menu->texts[12].size = 60;
    menu->texts[12].textHOffset = -10;
    create_text(&menu->texts[12], renderer, lang->solo, DNFONT);

    menu->texts[13].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[13].size = 60;
    menu->texts[13].textHOffset = -10;
    create_text(&menu->texts[13], renderer, lang->solo, DNFONTOUTLINED);

    menu->texts[14].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[14].size = 120;
    create_text(&menu->texts[14], renderer, lang->type_ip_addr, DNFONT);

    menu->texts[15].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[15].size = 120;
    create_text(&menu->texts[15], renderer, lang->press_enter_to_confirm, DNFONT);

    menu->texts[16].color = (SDL_Color){221, 21, 0, 255};
    menu->texts[16].size = 60;
    menu->texts[16].textHOffset = -10;

    create_text(&menu->texts[16], renderer, lang->host, DNFONT);

    menu->texts[17].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[17].size = 60;
    menu->texts[17].textHOffset = -10;

    create_text(&menu->texts[17], renderer, lang->host, DNFONTOUTLINED);

    menu->texts[18].color = (SDL_Color){221, 21, 0, 255};
    menu->texts[18].size = 60;
    menu->texts[18].textHOffset = -10;

    create_text(&menu->texts[18], renderer, lang->join, DNFONT);

    menu->texts[19].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[19].size = 60;
    menu->texts[19].textHOffset = -10;

    create_text(&menu->texts[19], renderer, lang->join, DNFONTOUTLINED);

    t_RGB color = {255, 255, 255, 0};
    SDL_Rect coords = {20, 20, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &change_menu_to_main_menu, coords, color, color, &menu->texts[2], &menu->texts[1], 3);

    coords = (SDL_Rect){400, (1080 / 2 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &start_level_1, coords, color, color, &menu->texts[4], &menu->texts[3], 3);

    coords = (SDL_Rect){(1920 / 2 - (win->menus.main.button.w / 5 / 2)), (1080 / 2 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &start_level_2, coords, color, color, &menu->texts[6], &menu->texts[5], 3);

    coords = (SDL_Rect){1520 - win->menus.main.button.w / 5, (1080 / 2 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &start_level_3, coords, color, color, &menu->texts[8], &menu->texts[7], 3);

    coords = (SDL_Rect){(1920 / 2 - (win->menus.main.button.w / 5 / 2)), (1000 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &change_menu_to_multi_lobby, coords, color, color, &menu->texts[10], &menu->texts[9], 3);

    /*MULTI PART*/
    coords = (SDL_Rect){20, 20, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &change_menu_to_main_menu, coords, color, color, &menu->texts[2], &menu->texts[1], 4);

    coords = (SDL_Rect){400, 850, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &start_level_1, coords, color, color, &menu->texts[4], &menu->texts[3], 4);

    coords = (SDL_Rect){(1920 / 2 - (win->menus.main.button.w / 5 / 2)), 850, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &start_level_2, coords, color, color, &menu->texts[6], &menu->texts[5], 4);

    coords = (SDL_Rect){1520 - win->menus.main.button.w / 5, 850, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &start_level_3, coords, color, color, &menu->texts[8], &menu->texts[7], 4);

    coords = (SDL_Rect){400, (1000 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &change_menu_to_solo_lobby, coords, color, color, &menu->texts[13], &menu->texts[12], 4);

    coords = (SDL_Rect){(1920 / 2 - (win->menus.main.button.w / 5 / 2)), (1000 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &host_game, coords, color, color, &menu->texts[17], &menu->texts[16], 4);

    coords = (SDL_Rect){1520 - win->menus.main.button.w / 5, (1000 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &draw_enter_host_addr, coords, color, color, &menu->texts[19], &menu->texts[18], 4);

    return ((void *)1);
}

int init_lobby_menu(t_game *game, SDL_Renderer *renderer,
                    t_lobby *lobby)
{
    pthread_t threads[9];
    void *ret = NULL;
    int finalRet = 1;

    ft_bzero(lobby, sizeof(t_lobby));
    t_png *images[8] = {
        &lobby->background,
        &lobby->multi_background,
        &lobby->button,
        &lobby->playerImgs[0],
        &lobby->playerImgs[1],
        &lobby->playerImgs[2],
        &lobby->playerImgs[3],
        &lobby->playerImgs[4],
    };
    const char *paths[8] = {
        "assets/png/lobby/solo/background.png",
        "assets/png/lobby/multiplayer/multiplayer_bg.png",
        "assets/png/main_menu/button.png",
        "assets/png/player/ply_front_idle.png",
        "assets/png/player/ply_front_walk.png",
        "assets/png/player/player_idle_edge_2.png",
        "assets/png/player/player_back.png",
        "assets/png/player/player_back_walk.png"};

    for (int i = 0; i < 8; i++)
        images[i]->path = ft_strdup(paths[i]);

    for (int i = 0; i < 8; i++)
        pthread_create(&threads[i], NULL, process_png, images[i]);

    pthread_create(&threads[8], NULL, init_texts, game);

    for (int i = 0; i < 8; i++)
    {
        pthread_join(threads[i], &ret);

        if (!ret)
            finalRet = 0;
        else
            images[i]->texture =
                create_image(images[i], renderer);
    }
    pthread_join(threads[8], &ret);

    if (!ret)
        finalRet = 0;
    return finalRet;
}

static void draw_texts(t_game *game, t_lobby *menu)
{
    draw_texture(1920 / 2 - (menu->texts[0].w / 2), 150, menu->texts[0].w, menu->texts[0].h, game->window, menu->texts[0].texture);
}
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
