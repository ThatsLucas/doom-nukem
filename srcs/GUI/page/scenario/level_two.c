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

/* Affiche les textes de la page courante. */
static void draw_texts(Uint64 curTime, Uint64 Begin, t_cinematic *menu, t_WIN *win)
{
    Uint64 part = CINEMATIC_ONE_DURATION / 3;
    Uint64 diff = curTime - Begin;

    if (diff < part)
        draw_cinematic_subtitle(menu, win, 4);
    else if (diff < part * 2)
        draw_cinematic_subtitle(menu, win, 5);
    else
        draw_cinematic_subtitle(menu, win, 6);
}

/* Affiche la cinématique du niveau 2. */
void draw_cinematic_two(t_game *game)
{
    t_WIN *win = game->window;
    t_cinematic *menu = &win->menus.cinematic;
    Uint64 curTime = SDL_GetTicks64();

    update_light_pulse(menu, cinematic_delta(menu, curTime));

    draw_texture(0, 0, 1920, 1080, win, menu->bg_two.texture);
    draw_texture(800, 300, menu->blue_light.w / 5 + menu->blue_light_ratio, menu->blue_light.h / 5 + menu->blue_light_ratio, win, menu->blue_light.texture);
    draw_cinematic_bars((t_RGB){0, 0, 0, 255}, game->window);
    draw_texts(curTime, menu->cinematatic_begin_time, menu, win);

    end_cinematic_if_over(game, menu, curTime);
}
