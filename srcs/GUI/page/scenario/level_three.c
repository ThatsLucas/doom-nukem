/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:28:59 by lle-duc           #+#    #+#             */
/*   Updated: 2026/06/10 14:24:11 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

static void draw_texts(Uint64 curTime, Uint64 Begin, t_cinematic *menu, t_WIN *win)
{
    Uint64 part = CINEMATIC_ONE_DURATION / 9;
    Uint64 diff = curTime - Begin;
    if (diff < part)
        draw_texture(1920 / 2 - menu->texts[7].w / 2, 950, menu->texts[7].w, menu->texts[7].h, win, menu->texts[7].texture);
    else if (diff < part * 2)
        draw_texture(1920 / 2 - menu->texts[8].w / 2, 950, menu->texts[8].w, menu->texts[8].h, win, menu->texts[8].texture);
    else if (diff < part * 3)
        draw_texture(1920 / 2 - menu->texts[9].w / 2, 950, menu->texts[9].w, menu->texts[9].h, win, menu->texts[9].texture);
    else if (diff < part * 4)
        draw_texture(1920 / 2 - menu->texts[10].w / 2, 950, menu->texts[10].w, menu->texts[10].h, win, menu->texts[10].texture);
    else if (diff < part * 5)
        draw_texture(1920 / 2 - menu->texts[11].w / 2, 950, menu->texts[11].w, menu->texts[11].h, win, menu->texts[11].texture);
    else if (diff < part * 6)
        draw_texture(1920 / 2 - menu->texts[12].w / 2, 950, menu->texts[12].w, menu->texts[12].h, win, menu->texts[12].texture);
    else if (diff < part * 7)
        draw_texture(1920 / 2 - menu->texts[13].w / 2, 950, menu->texts[13].w, menu->texts[13].h, win, menu->texts[13].texture);
    else if (diff < part * 8)
        draw_texture(1920 / 2 - menu->texts[14].w / 2, 950, menu->texts[14].w, menu->texts[14].h, win, menu->texts[14].texture);
    else if (diff < part * 9)
        draw_texture(1920 / 2 - menu->texts[15].w / 2, 950, menu->texts[15].w, menu->texts[15].h, win, menu->texts[15].texture);
}

void draw_cinematic_three(t_game *game)
{
    t_WIN *win = game->window;
    t_cinematic *menu = &win->menus.cinematic;
    Uint64 curTime = SDL_GetTicks64();

    if (!menu->last_time)
        menu->last_time = curTime;
    float delta = (curTime - menu->last_time) / 1000.0f;

    // px per sec
    menu->blue_light_ratio -= 30 * delta * menu->grow_order;
    menu->last_time = curTime;

    if (menu->blue_light_ratio < -70.0f)
        menu->grow_order = -1;
    else if (menu->blue_light_ratio > 70.0f)
        menu->grow_order = 1;

    if (menu->blue_light_ratio < -70)
        menu->blue_light_ratio = -70;

    draw_texture(0, 0, 1920, 1080, win, menu->bg_three.texture);
    draw_texture(1920 / 2 - (menu->eyes.w / 2 + menu->blue_light_ratio) / 2, 400 - menu->blue_light_ratio, menu->eyes.w / 2 + menu->blue_light_ratio, menu->eyes.h / 2 + menu->blue_light_ratio, win, menu->eyes.texture);

    int rng = curTime % 10;
    if (rng < 4)
        draw_texture(50 + (40 * rng), 0, menu->lightning.w, menu->lightning.h, win, menu->lightning.texture);
    else if (rng > 4 && rng < 8)
        draw_texture(1200 - (40 * rng), 0, menu->lightning.w, menu->lightning.h, win, menu->lightning.texture);

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
