/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:28:48 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/20 15:33:25 by lle-duc          ###   ########.fr       */
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
    t_cinematic *menu = &win->menus.cinematic;

    menu->texts[0].size = 60;
    menu->texts[0].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[1].size = 60;
    menu->texts[1].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[2].size = 60;
    menu->texts[2].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[3].size = 60;
    menu->texts[3].color = (SDL_Color){255, 255, 255, 255};

    create_text(&menu->texts[0], renderer, lang->cinematic_text_one, DNFONT);
    create_text(&menu->texts[1], renderer, lang->cinematic_text_two, DNFONT);
    create_text(&menu->texts[2], renderer, lang->cinematic_text_three, DNFONT);
    create_text(&menu->texts[3], renderer, lang->cinematic_text_four, DNFONT);

    return ((void *)1);
}

int init_cinematics_menus(t_game *game, SDL_Renderer *renderer,
                          t_cinematic *cinematic)
{
    pthread_t threads[8];
    void *ret = NULL;
    int finalRet = 1;

    ft_bzero(cinematic, sizeof(t_cinematic));
    t_png *images[7] = {
        &cinematic->bg_one,
        &cinematic->scientifics[0],
        &cinematic->scientifics[1],
        &cinematic->scientifics[2],
        &cinematic->scientifics[3],
        &cinematic->scientifics[4],
        &cinematic->smoke,
    };

    cinematic->scientificsXPos[0] = 1700.0f;
    cinematic->scientificsXPos[1] = 1200.0f;
    cinematic->scientificsXPos[2] = 800.0f;
    cinematic->scientificsXPos[3] = 400.0f;
    cinematic->scientificsXPos[4] = 200.0f;
    cinematic->scientifics[0].y = 500;
    cinematic->scientifics[1].y = 500;
    cinematic->scientifics[2].y = 500;
    cinematic->scientifics[3].y = 500;
    cinematic->scientifics[4].y = 500;
    cinematic->smoke.x = 0;
    cinematic->smokeYPos = 600.0f;

    const char *paths[7] = {
        "assets/png/cinematics/bg_one.png",
        "assets/png/cinematics/scientific_one.png",
        "assets/png/cinematics/scientific_two.png",
        "assets/png/cinematics/scientific_three.png",
        "assets/png/cinematics/scientific_four.png",
        "assets/png/cinematics/scientific_five.png",
        "assets/png/cinematics/smoke.png",
    };

    for (int i = 0; i < 7; i++)
        images[i]->path = ft_strdup(paths[i]);

    for (int i = 0; i < 7; i++)
        pthread_create(&threads[i], NULL, process_png, images[i]);

    pthread_create(&threads[7], NULL, init_texts, game);

    for (int i = 0; i < 7; i++)
    {
        pthread_join(threads[i], &ret);

        if (!ret)
            finalRet = 0;
        else
            images[i]->texture =
                create_image(images[i], renderer);
    }
    pthread_join(threads[7], &ret);

    if (!ret)
        finalRet = 0;
    return finalRet;
}

static void draw_texts(Uint64 curTime, Uint64 Begin, t_cinematic *menu, t_WIN *win)
{
    Uint64 part = CINEMATIC_ONE_DURATION / 4;
    Uint64 diff = curTime - Begin;

    if (diff < part)
        draw_texture(1920 / 2 - menu->texts[0].w / 2, 950, menu->texts[0].w, menu->texts[0].h, win, menu->texts[0].texture);
    else if (diff < part * 2)
        draw_texture(1920 / 2 - menu->texts[1].w / 2, 950, menu->texts[1].w, menu->texts[1].h, win, menu->texts[1].texture);
    else if (diff < part * 3)
        draw_texture(1920 / 2 - menu->texts[2].w / 2, 950, menu->texts[2].w, menu->texts[2].h, win, menu->texts[2].texture);
    else
        draw_texture(1920 / 2 - menu->texts[3].w / 2, 950, menu->texts[3].w, menu->texts[3].h, win, menu->texts[3].texture);
}

void draw_cinematic_one(t_game *game)
{
    // SDL_Renderer *renderer = game->window->renderPTR;
    t_WIN *win = game->window;
    t_cinematic *menu = &win->menus.cinematic;
    Uint64 curTime = SDL_GetTicks64();

    if (!menu->last_time)
        menu->last_time = curTime;
    float delta = (curTime - menu->last_time) / 1000.0f;

    // px per sec
    menu->scientificsXPos[0] -= 50 * delta;
    menu->scientificsXPos[1] -= 60 * delta;
    menu->scientificsXPos[2] += 35 * delta;
    menu->scientificsXPos[3] += 10 * delta;
    menu->scientificsXPos[4] += 65 * delta;
    menu->smokeYPos -= 20 * delta;
    menu->last_time = curTime;

    draw_texture(0, 0, 1920, 1080, win, menu->bg_one.texture);
    draw_texture(menu->scientificsXPos[0], menu->scientifics[0].y, menu->scientifics[0].w, menu->scientifics[0].h, win, menu->scientifics[0].texture);
    draw_texture(menu->scientificsXPos[1], menu->scientifics[1].y, menu->scientifics[1].w, menu->scientifics[1].h, win, menu->scientifics[1].texture);
    draw_texture(menu->scientificsXPos[2], menu->scientifics[2].y, menu->scientifics[2].w, menu->scientifics[2].h, win, menu->scientifics[2].texture);
    draw_texture(menu->scientificsXPos[3], menu->scientifics[3].y, menu->scientifics[3].w, menu->scientifics[3].h, win, menu->scientifics[3].texture);
    draw_texture(menu->scientificsXPos[4], menu->scientifics[4].y, menu->scientifics[4].w, menu->scientifics[4].h, win, menu->scientifics[4].texture);
    draw_texture(menu->smoke.x, menu->smokeYPos, 1920, menu->smoke.h, win, menu->smoke.texture);
    draw_cinematic_bars((t_RGB){0, 0, 0, 255}, game->window);
    draw_texts(curTime, menu->cinematatic_begin_time, menu, win);

    if (!menu->cinematatic_begin_time)
        menu->cinematatic_begin_time = curTime;
    if (menu->cinematatic_begin_time + menu->cinematatic_duration < curTime)
    {
        menu->cinematatic_begin_time = 0;
        menu->cinematatic_duration = 0;
        game->window->menus.current = 0;
        return;
    }
}
