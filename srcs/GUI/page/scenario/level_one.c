/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:28:48 by lle-duc           #+#    #+#             */
/*   Updated: 2026/06/10 14:21:25 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

static void draw_texts(Uint64 curTime, Uint64 Begin, t_cinematic *menu, t_WIN *win)
{
    Uint64 part = CINEMATIC_ONE_DURATION / 4;
    Uint64 diff = curTime - Begin;

    if (diff < part)
        draw_cinematic_subtitle(menu, win, 0);
    else if (diff < part * 2)
        draw_cinematic_subtitle(menu, win, 1);
    else if (diff < part * 3)
        draw_cinematic_subtitle(menu, win, 2);
    else
        draw_cinematic_subtitle(menu, win, 3);
}

/* Scientists walking and smoke rising */
static void move_cinematic_one(t_cinematic *menu, float delta)
{
    // px per sec
    menu->scientificsXPos[0] -= 50 * delta;
    menu->scientificsXPos[1] -= 60 * delta;
    menu->scientificsXPos[2] += 35 * delta;
    menu->scientificsXPos[3] += 10 * delta;
    menu->scientificsXPos[4] += 65 * delta;
    menu->smokeYPos -= 20 * delta;
}

void draw_cinematic_one(t_game *game)
{
    t_WIN *win = game->window;
    t_cinematic *menu = &win->menus.cinematic;
    Uint64 curTime = SDL_GetTicks64();

    move_cinematic_one(menu, cinematic_delta(menu, curTime));

    draw_texture(0, 0, 1920, 1080, win, menu->bg_one.texture);
    for (int i = 0; i < 5; i++)
        draw_texture(menu->scientificsXPos[i], menu->scientifics[i].y, menu->scientifics[i].w, menu->scientifics[i].h, win, menu->scientifics[i].texture);
    draw_texture(menu->smoke.x, menu->smokeYPos, 1920, menu->smoke.h, win, menu->smoke.texture);
    draw_cinematic_bars((t_RGB){0, 0, 0, 255}, game->window);
    draw_texts(curTime, menu->cinematatic_begin_time, menu, win);

    end_cinematic_if_over(game, menu, curTime);
}
