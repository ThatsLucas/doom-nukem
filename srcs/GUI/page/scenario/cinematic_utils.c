/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinematic_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:14:19 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:14:19 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

/* Calcule le temps écoulé depuis la dernière image. */
float cinematic_delta(t_cinematic *menu, Uint64 curTime)
{
    float delta;

    if (!menu->last_time)
        menu->last_time = curTime;
    delta = (curTime - menu->last_time) / 1000.0f;
    menu->last_time = curTime;
    if (delta > 0.1f)
        delta = 0.1f;
    return (delta);
}

/* Fait pulser la lumière de la cinématique. */
void update_light_pulse(t_cinematic *menu, float delta)
{
    // px per sec
    menu->blue_light_ratio -= 30 * delta * menu->grow_order;

    if (menu->blue_light_ratio < -70.0f)
        menu->grow_order = -1;
    else if (menu->blue_light_ratio > 70.0f)
        menu->grow_order = 1;

    if (menu->blue_light_ratio < -70)
        menu->blue_light_ratio = -70;
    else if (menu->blue_light_ratio > 70)
        menu->blue_light_ratio = 70;
}

/* Affiche un sous-titre de la cinématique. */
void draw_cinematic_subtitle(t_cinematic *menu, t_WIN *win, int idx)
{
    draw_texture(1920 / 2 - menu->texts[idx].w / 2, 950, menu->texts[idx].w, menu->texts[idx].h, win, menu->texts[idx].texture);
}

/* Lance le niveau quand la cinématique est terminée. */
void end_cinematic_if_over(t_game *game, t_cinematic *menu, Uint64 curTime)
{
    if (!menu->cinematatic_begin_time)
        menu->cinematatic_begin_time = curTime;
    if (menu->cinematatic_begin_time + menu->cinematatic_duration < curTime)
    {
        menu->cinematatic_begin_time = 0;
        menu->cinematatic_duration = 0;
        menu->last_time = 0;
        game->window->menus.current = 0;
    }
}
