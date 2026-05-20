/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:28:48 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/20 14:09:00 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"
// #include "../../../includes/GUI.h"

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

    return ((void *)1);
}

int init_cinematics_menus(t_game *game, SDL_Renderer *renderer,
                          t_cinematic *cinematic)
{
    pthread_t threads[5];
    void *ret = NULL;
    int finalRet = 1;

    ft_bzero(cinematic, sizeof(t_cinematic));
    t_png *images[4] = {
        &cinematic->bg_one,
        &cinematic->scientifics[0],
        &cinematic->scientifics[1],
        &cinematic->smoke,
    };

    cinematic->scientifics[0].x = 1500;
    cinematic->scientifics[0].y = 500;
    cinematic->scientifics[1].x = 1000;
    cinematic->scientifics[1].y = 500;
    cinematic->smoke.x = 0;
    cinematic->smoke.y = 600;

    const char *paths[4] = {
        "assets/png/cinematics/bg_one.png",
        "assets/png/cinematics/scientific_one.png",
        "assets/png/cinematics/scientific_two.png",
        "assets/png/cinematics/smoke.png",
    };

    for (int i = 0; i < 4; i++)
        images[i]->path = ft_strdup(paths[i]);

    for (int i = 0; i < 4; i++)
        pthread_create(&threads[i], NULL, process_png, images[i]);

    pthread_create(&threads[4], NULL, init_texts, game);

    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], &ret);

        if (!ret)
            finalRet = 0;
        else
            images[i]->texture =
                create_image(images[i], renderer);
    }
    pthread_join(threads[4], &ret);

    if (!ret)
        finalRet = 0;
    return finalRet;
}

void draw_cinematic_one(t_game *game)
{
    // SDL_Renderer *renderer = game->window->renderPTR;
    t_WIN *win = game->window;
    t_cinematic *menu = &win->menus.cinematic;

    draw_texture(0, 0, 1920, 1080, win, menu->bg_one.texture);
    draw_texture(menu->scientifics[0].x, menu->scientifics[0].y, menu->scientifics[0].w, menu->scientifics[0].h, win, menu->scientifics[0].texture);
    draw_texture(menu->scientifics[1].x, menu->scientifics[1].y, menu->scientifics[1].w, menu->scientifics[1].h, win, menu->scientifics[1].texture);
    draw_texture(menu->smoke.x, menu->smoke.y, 1920, menu->smoke.h, win, menu->smoke.texture);
    draw_cinematic_bars((t_RGB){0, 0, 0, 255}, game->window);

    Uint64 curTime = SDL_GetTicks64();
    if (!menu->cinematatic_begin_time)
        menu->cinematatic_begin_time = curTime;
    if (menu->cinematatic_begin_time + menu->cinematatic_duration < curTime)
    {
        menu->cinematatic_begin_time = 0;
        menu->cinematatic_duration = 0;
        game->window->menus.current = 0;
        return;
    }
    if (curTime % 3 == 1)
    {
        menu->scientifics[0].x -= 1;
        menu->scientifics[1].x -= 2;
        menu->smoke.y -= 1;
    }
}
