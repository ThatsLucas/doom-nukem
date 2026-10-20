/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby_init.c                                       :+:      :+:    :+:   */
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

/* Initialise les boutons du salon solo. */
static void init_solo_buttons(t_WIN *win, t_lobby *menu)
{
    t_RGB color = {255, 255, 255, 0};
    int bw = win->menus.main.button.w / 5;
    int bh = win->menus.main.button.h / 5;

    create_button(&win->buttonList, &lobby_to_main_menu, (SDL_Rect){20, 20, bw, bh}, color, color, &menu->texts[2], &menu->texts[1], 3);
    create_button(&win->buttonList, &start_level_1, (SDL_Rect){400, 1080 / 2 - bh / 2, bw, bh}, color, color, &menu->texts[4], &menu->texts[3], 3);
    create_button(&win->buttonList, &start_level_2, (SDL_Rect){1920 / 2 - bw / 2, 1080 / 2 - bh / 2, bw, bh}, color, color, &menu->texts[6], &menu->texts[5], 3);
    create_button(&win->buttonList, &start_level_3, (SDL_Rect){1520 - bw, 1080 / 2 - bh / 2, bw, bh}, color, color, &menu->texts[8], &menu->texts[7], 3);
    create_button(&win->buttonList, &lobby_to_multi_lobby, (SDL_Rect){1920 / 2 - bw / 2, 1000 - bh / 2, bw, bh}, color, color, &menu->texts[10], &menu->texts[9], 3);
}

/* Initialise les boutons du salon multijoueur. */
static void init_multi_buttons(t_WIN *win, t_lobby *menu)
{
    t_RGB color = {255, 255, 255, 0};
    int bw = win->menus.main.button.w / 5;
    int bh = win->menus.main.button.h / 5;

    create_button(&win->buttonList, &lobby_to_main_menu, (SDL_Rect){20, 20, bw, bh}, color, color, &menu->texts[2], &menu->texts[1], 4);
    create_button(&win->buttonList, &start_level_1, (SDL_Rect){400, 850, bw, bh}, color, color, &menu->texts[4], &menu->texts[3], 4);
    create_button(&win->buttonList, &start_level_2, (SDL_Rect){1920 / 2 - bw / 2, 850, bw, bh}, color, color, &menu->texts[6], &menu->texts[5], 4);
    create_button(&win->buttonList, &start_level_3, (SDL_Rect){1520 - bw, 850, bw, bh}, color, color, &menu->texts[8], &menu->texts[7], 4);
    create_button(&win->buttonList, &lobby_to_solo_lobby, (SDL_Rect){400, 1000 - bh / 2, bw, bh}, color, color, &menu->texts[13], &menu->texts[12], 4);
    create_button(&win->buttonList, &host_game, (SDL_Rect){1920 / 2 - bw / 2, 1000 - bh / 2, bw, bh}, color, color, &menu->texts[17], &menu->texts[16], 4);
    create_button(&win->buttonList, &draw_enter_host_addr, (SDL_Rect){1520 - bw, 1000 - bh / 2, bw, bh}, color, color, &menu->texts[19], &menu->texts[18], 4);
}

/* Initialise les textes du salon. */
static void *init_texts(void *gameStruct)
{
    t_game *game = (t_game *)gameStruct;
    t_WIN *win = game->window;

    init_lobby_texts(game);
    init_solo_buttons(win, &win->menus.lobby);
    init_multi_buttons(win, &win->menus.lobby);
    return ((void *)1);
}

/* Attend le chargement des images du salon et crée leurs textures. */
static int join_lobby_images(pthread_t *threads, t_png **images, t_lobby *lobby, SDL_Renderer *renderer)
{
    void *ret = NULL;
    int finalRet = 1;

    for (int i = 0; i < 8; i++)
    {
        pthread_join(threads[i], &ret);

        if (!ret)
            finalRet = 0;
        else
        {
            if (i >= 3)
                lobby->playerBounds[i - 3] = get_png_opaque_bounds(images[i]);
            images[i]->texture =
                create_image(images[i], renderer);
        }
    }
    return (finalRet);
}

/* Prépare les chemins des images du salon. */
static void set_lobby_images(t_lobby *lobby, t_png **images)
{
    t_png *list[8] = {
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
    {
        images[i] = list[i];
        images[i]->path = ft_strdup(paths[i]);
    }
}

/* Initialise le salon. */
int init_lobby_menu(t_game *game, SDL_Renderer *renderer,
                    t_lobby *lobby)
{
    pthread_t threads[9];
    void *ret = NULL;
    int finalRet;

    ft_bzero(lobby, sizeof(t_lobby));
    t_png *images[8];

    set_lobby_images(lobby, images);

    for (int i = 0; i < 8; i++)
        pthread_create(&threads[i], NULL, process_png, images[i]);

    pthread_create(&threads[8], NULL, init_texts, game);

    finalRet = join_lobby_images(threads, images, lobby, renderer);
    pthread_join(threads[8], &ret);

    if (!ret)
        finalRet = 0;
    return finalRet;
}
