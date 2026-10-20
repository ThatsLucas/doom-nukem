/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs_sliders.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:10:24 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:10:24 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

/* Règle la sensibilité de la souris avec le curseur. */
int grab_mouse_sensibility(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click)
{
    if (!menu->isGrabbingSliderMouseSensi && !click)
        return (0);
    SDL_Rect mouseCoords = {MouseDatas->x - (game->window->w - menu->ViewPortCoords.w) / 2, MouseDatas->y - menu->ViewPortCoords.y, 0, 0};
    SDL_Rect sliderCoords = menu->MouseSensiCoords;
    to_responsive(game->window, &sliderCoords);
    if (!menu->isGrabbingSliderMouseSensi)
    {
        if (!is_mouse_pos_inside_button(mouseCoords, sliderCoords))
            return (0);
        menu->isGrabbingSliderMouseSensi = 1;
    }

    int32_t newX = menu->MouseSensiCoords.x;

    if (MouseDatas->xrel > 1000 || MouseDatas->xrel < -1000) // big value frist click
        MouseDatas->xrel = 0;
    newX += MouseDatas->xrel;

    game->settings.MouseSensibility += ((float)MouseDatas->xrel) * ((MAX_MOUSE_SENSIBILITY - MIN_MOUSE_SENSIBILITY) / 480);
    if (newX < 200)
    {
        newX = 200;
        game->settings.MouseSensibility = MIN_MOUSE_SENSIBILITY;
    }
    else if (newX > 680)
    {
        newX = 680;
        game->settings.MouseSensibility = MAX_MOUSE_SENSIBILITY;
    }
    menu->MouseSensiCoords.x = newX;
    return (1);
}

/* Règle le champ de vision avec le curseur. */
int grab_fov(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click)
{
    if (!menu->isGrabbingSlider && !click)
        return (0);
    SDL_Rect mouseCoords = {MouseDatas->x - (game->window->w - menu->ViewPortCoords.w) / 2, MouseDatas->y - menu->ViewPortCoords.y, 0, 0};
    SDL_Rect sliderCoords = {menu->slider_grab.x, menu->slider_grab.y, menu->slider_grab.w / 6, menu->slider_grab.h / 6};
    to_responsive(game->window, &sliderCoords);
    if (!menu->isGrabbingSlider)
    {
        if (!is_mouse_pos_inside_button(mouseCoords, sliderCoords))
            return (0);
        menu->isGrabbingSlider = 1;
    }
    if (MouseDatas->xrel > 1000 || MouseDatas->xrel < -1000) // big value frist click
        MouseDatas->xrel = 0;
    menu->slider_grab.x += MouseDatas->xrel;
    game->settings.FOV += ((float)MouseDatas->xrel) * ((MAX_FOV - MIN_FOV) / 480);
    if (menu->slider_grab.x < 200)
    {
        menu->slider_grab.x = 200;
        game->settings.FOV = MIN_FOV;
    }
    else if (menu->slider_grab.x > 680)
    {
        menu->slider_grab.x = 680;
        game->settings.FOV = MAX_FOV;
    }
    return (1);
}

/* Fait défiler les paramètres avec la molette. */
void handle_settings_scroll_mouse_wheel(t_game *game, t_settings_menu *menu, SDL_MouseWheelEvent *wheel)
{
    int minScrollY = 40;
    int maxScrollY = 1040 - (int)menu->scroll_grab.h / 14;

    int scroll = wheel->y;
    if (wheel->direction == SDL_MOUSEWHEEL_FLIPPED)
        scroll *= -1;
    if (scroll > 1000 || scroll < -1000) // big value frist click
        scroll = 0;
    menu->scrollH += -scroll * 15;
    menu->scroll_grab.y += -scroll * 15;
    if (menu->scroll_grab.y < minScrollY)
        menu->scroll_grab.y = minScrollY;
    else if (menu->scroll_grab.y > maxScrollY)
        menu->scroll_grab.y = maxScrollY;
    game->window->menus.settings.scrollH = (int)(((float)(menu->scroll_grab.y - minScrollY) / (float)(maxScrollY - minScrollY)) * 2000.0f);
}

/* Fait défiler les paramètres avec la barre de défilement. */
int grab_scroll(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click)
{
    int minScrollY = 40;
    int maxScrollY = 1040 - (int)menu->scroll_grab.h / 14;

    if (!menu->isGrabbingScrollBar && !click)
        return (0);
    SDL_Rect mouseCoords = {MouseDatas->x, MouseDatas->y, 0, 0};
    SDL_Rect scrollCoords = {1890 - menu->scroll.w / 5 + (menu->scroll.w / 5 - menu->scroll_grab.w / 14) / 2, menu->scroll_grab.y, menu->scroll_grab.w / 14, menu->scroll_grab.h / 14};
    to_responsive(game->window, &scrollCoords);
    if (!menu->isGrabbingScrollBar)
    {
        if (!is_mouse_pos_inside_button(mouseCoords, scrollCoords))
            return (0);
        menu->isGrabbingScrollBar = 1;
    }

    if (MouseDatas->yrel > 1000 || MouseDatas->yrel < -1000) // big value frist click
        MouseDatas->yrel = 0;
    menu->scroll_grab.y += MouseDatas->yrel;
    if (menu->scroll_grab.y < minScrollY)
        menu->scroll_grab.y = minScrollY;
    else if (menu->scroll_grab.y > maxScrollY)
        menu->scroll_grab.y = maxScrollY;
    game->window->menus.settings.scrollH = (int)(((float)(menu->scroll_grab.y - minScrollY) / (float)(maxScrollY - minScrollY)) * 2000.0f);
    return (1);
}
