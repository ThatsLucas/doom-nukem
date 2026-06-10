/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:44:17 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/21 13:27:41 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

static void draw_texts(Uint64 curTime, Uint64 Begin, t_cinematic *menu, t_WIN *win)
{
    Uint64 part = CINEMATIC_ONE_DURATION / 3;
    Uint64 diff = curTime - Begin;

    if (diff < part)
        draw_texture(1920 / 2 - menu->texts[4].w / 2, 950, menu->texts[4].w, menu->texts[4].h, win, menu->texts[4].texture);
    else if (diff < part * 2)
        draw_texture(1920 / 2 - menu->texts[5].w / 2, 950, menu->texts[5].w, menu->texts[5].h, win, menu->texts[5].texture);
    else
        draw_texture(1920 / 2 - menu->texts[6].w / 2, 950, menu->texts[6].w, menu->texts[6].h, win, menu->texts[6].texture);
}

void draw_cinematic_two(t_game *game)
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

    draw_texture(0, 0, 1920, 1080, win, menu->bg_two.texture);
    draw_texture(800, 300, menu->blue_light.w / 5 + menu->blue_light_ratio, menu->blue_light.h / 5 + menu->blue_light_ratio, win, menu->blue_light.texture);
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
