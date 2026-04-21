// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   handle_click.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/04/20 15:59:19 by lle-duc           #+#    #+#             */
// /*   Updated: 2026/04/20 18:15:53 by lle-duc          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

static int is_mouse_pos_inside_button(SDL_Rect mouseCoords, SDL_Rect buttonCoords)
{
    if (mouseCoords.x < buttonCoords.x || mouseCoords.x > buttonCoords.x  + buttonCoords.w)
        return 0;
    if (mouseCoords.y < buttonCoords.y || mouseCoords.y > buttonCoords.y  + buttonCoords.h)
        return 0;
    return 1;
}

static int grab_fov(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click)
{
    if (!menu->isGrabbingSlider && !click)
        return (0);
    SDL_Rect mouseCoords = {MouseDatas->x - (1920 - 1044) / 2, MouseDatas->y - 136, 0, 0};
    SDL_Rect sliderCoords = {menu->slider_grab.x, menu->slider_grab.y, menu->slider_grab.w/6, menu->slider_grab.h/6};
    to_responsive(game->window, &mouseCoords);
    to_responsive(game->window, &sliderCoords);
    if (!menu->isGrabbingSlider)
    {
        if (!is_mouse_pos_inside_button(mouseCoords, sliderCoords))
            return (0);
        menu->isGrabbingSlider = 1;
    }
    if (MouseDatas->xrel > 1000) // big value frist click
        MouseDatas->xrel = 0;
    menu->slider_grab.x += MouseDatas->xrel;
    if (menu->slider_grab.x < (game->window->w * 200) / 1920)
        menu->slider_grab.x = 200;
    else if (menu->slider_grab.x > (game->window->w * 680) / 1920)
        menu->slider_grab.x = 680;
    ft_printf("New pos = %d, xrel = %d\n", menu->slider_grab.x, MouseDatas->xrel);
    return (1);
}

void handle_settings_click(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click)
{
    if (grab_fov(game, menu, MouseDatas, click))
        return;
}

void handle_settings_released(t_settings_menu *menu)
{
    if (menu->isGrabbingSlider)
    {
        menu->isGrabbingSlider = 0;
        ft_printf("released received, slidder = %d\n", menu->isGrabbingSlider);
        return;
    }

    if (menu->isGrabbingScrollBar)
    {
        menu->isGrabbingScrollBar = 0;
        return;
    }
}