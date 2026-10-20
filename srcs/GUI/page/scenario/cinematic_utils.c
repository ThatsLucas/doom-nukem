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

/* Time since the last frame in seconds, and saves the current time */
float cinematic_delta(t_cinematic *menu, Uint64 curTime)
{
    float delta;

    if (!menu->last_time)
        menu->last_time = curTime;
    delta = (curTime - menu->last_time) / 1000.0f;
    menu->last_time = curTime;
    return (delta);
}

/* Grows and shrinks blue_light_ratio between -70 and 70 */
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
}

/* Subtitle number idx, centered at the bottom of the screen */
void draw_cinematic_subtitle(t_cinematic *menu, t_WIN *win, int idx)
{
    draw_texture(1920 / 2 - menu->texts[idx].w / 2, 950, menu->texts[idx].w, menu->texts[idx].h, win, menu->texts[idx].texture);
}

/* Starts the timer on the first frame and goes back to the game at the end */
void end_cinematic_if_over(t_game *game, t_cinematic *menu, Uint64 curTime)
{
    if (!menu->cinematatic_begin_time)
        menu->cinematatic_begin_time = curTime;
    if (menu->cinematatic_begin_time + menu->cinematatic_duration < curTime)
    {
        menu->cinematatic_begin_time = 0;
        menu->cinematatic_duration = 0;
        game->window->menus.current = 0;
    }
}
