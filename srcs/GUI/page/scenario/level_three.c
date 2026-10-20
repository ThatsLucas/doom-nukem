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

/* 9 subtitles (texts[7] to texts[15]) shown one after the other */
static void draw_texts(Uint64 curTime, Uint64 Begin, t_cinematic *menu, t_WIN *win)
{
    Uint64 part = CINEMATIC_ONE_DURATION / 9;
    Uint64 diff = curTime - Begin;

    for (Uint64 i = 0; i < 9; i++)
    {
        if (diff < part * (i + 1))
        {
            draw_cinematic_subtitle(menu, win, 7 + i);
            return ;
        }
    }
}

/* Random lightning on the left or the right */
static void draw_lightning(t_cinematic *menu, t_WIN *win, Uint64 curTime)
{
    int rng = curTime % 10;

    if (rng < 4)
        draw_texture(50 + (40 * rng), 0, menu->lightning.w, menu->lightning.h, win, menu->lightning.texture);
    else if (rng > 4 && rng < 8)
        draw_texture(1200 - (40 * rng), 0, menu->lightning.w, menu->lightning.h, win, menu->lightning.texture);
}

void draw_cinematic_three(t_game *game)
{
    t_WIN *win = game->window;
    t_cinematic *menu = &win->menus.cinematic;
    Uint64 curTime = SDL_GetTicks64();

    update_light_pulse(menu, cinematic_delta(menu, curTime));

    draw_texture(0, 0, 1920, 1080, win, menu->bg_three.texture);
    draw_texture(1920 / 2 - (menu->eyes.w / 2 + menu->blue_light_ratio) / 2, 400 - menu->blue_light_ratio, menu->eyes.w / 2 + menu->blue_light_ratio, menu->eyes.h / 2 + menu->blue_light_ratio, win, menu->eyes.texture);
    draw_lightning(menu, win, curTime);

    draw_cinematic_bars((t_RGB){0, 0, 0, 255}, game->window);
    draw_texts(curTime, menu->cinematatic_begin_time, menu, win);

    end_cinematic_if_over(game, menu, curTime);
}
