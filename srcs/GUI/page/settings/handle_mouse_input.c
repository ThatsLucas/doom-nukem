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
    if (mouseCoords.x < buttonCoords.x || mouseCoords.x > buttonCoords.x + buttonCoords.w)
        return 0;
    if (mouseCoords.y < buttonCoords.y || mouseCoords.y > buttonCoords.y + buttonCoords.h)
        return 0;
    return 1;
}

static int handle_language_selection(t_game *game, t_settings_menu *menu,
                                     SDL_MouseMotionEvent *MouseDatas, int click)
{
    SDL_Rect mouseCoords;
    int keyH;
    int yPos;
    int separatorH;
    int languageXOffset;

    if (!click)
        return (0);
    mouseCoords.x = MouseDatas->x - (game->window->w - menu->ViewPortCoords.w) / 2;
    mouseCoords.y = MouseDatas->y - menu->ViewPortCoords.y;
    mouseCoords.w = 0;
    mouseCoords.h = 0;
    if (mouseCoords.x < 0 || mouseCoords.x > menu->ViewPortCoords.w || mouseCoords.y < 0 || mouseCoords.y > menu->ViewPortCoords.h)
        return (0);

    keyH = menu->keys.h / 8;
    yPos = (keyH + 20) * 3;
    separatorH = menu->separator.h / 1.8;
    yPos += 150 + separatorH + 20 + menu->texts[3].h + 20 + 60;
    yPos += 150 + separatorH + 20 + menu->texts[4].h + 20;
    languageXOffset = (1044 - (20 * 3 + (menu->languages[0].w / 9 * 4))) / 2;
    for (int i = 0; i < 4; i++)
    {
        SDL_Rect languageCoords = {
            languageXOffset,
            yPos + 25 - menu->scrollH,
            menu->languages[i].w / 9,
            menu->languages[i].h / 9};
        to_responsive(game->window, &languageCoords);
        if (is_mouse_pos_inside_button(mouseCoords, languageCoords))
        {
            if (game->selected_language == i)
                return (1);
            game->selected_language = i;
            free_languages(game);
            parse_languages(game, i);
            refresh_main_menu_texts(game);
            refresh_settings_texts(game, menu);
            return (1);
        }
        languageXOffset += menu->languages[i].w / 9 + 20;
    }
    return (0);
}

int handle_key_control_selected(t_game *game, int key)
{
    t_settings_menu *menu = &game->window->menus.settings;
    const char *keyName = SDL_GetKeyName(key);

    if (game->window->menus.current != 2)
        return (0);

    int controlAsked = menu->is_selecting_control;

    if (controlAsked == 1)
    {
        game->settings.move_forward = key;
        destroy_text_texture(&menu->texts[9]);
        create_text(&menu->texts[9], game->window->renderPTR, (char *)keyName,
                    DNFONT);
    }
    else if (controlAsked == 2)
    {
        game->settings.move_backward = key;
        destroy_text_texture(&menu->texts[10]);
        create_text(&menu->texts[10], game->window->renderPTR, (char *)keyName,
                    DNFONT);
    }
    else if (controlAsked == 3)
    {
        game->settings.move_left = key;
        destroy_text_texture(&menu->texts[11]);
        create_text(&menu->texts[11], game->window->renderPTR, (char *)keyName,
                    DNFONT);
    }
    else if (controlAsked == 4)
    {
        game->settings.move_right = key;
        destroy_text_texture(&menu->texts[12]);
        create_text(&menu->texts[12], game->window->renderPTR, (char *)keyName,
                    DNFONT);
    }

    menu->is_selecting_control = 0;
    return (1);
}

static int handle_click_control(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas)
{
    SDL_Rect mouseCoords = {MouseDatas->x - (game->window->w - menu->ViewPortCoords.w) / 2, MouseDatas->y - menu->ViewPortCoords.y, 0, 0};
    SDL_Rect keyCoords;

    for (int i = 0; i < 4; i++)
    {
        keyCoords = menu->keysCoords[i];
        to_responsive(game->window, &keyCoords);
        if (is_mouse_pos_inside_button(mouseCoords, keyCoords))
        {
            menu->is_selecting_control = i + 1;
            return (1);
        }
    }
    return (0);
}

static int grab_fov(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click)
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
    game->window->menus.settings.scrollH = (int)(((float)(menu->scroll_grab.y - minScrollY) / (float)(maxScrollY - minScrollY)) * 1600.0f);
}

static int grab_scroll(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click)
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
    game->window->menus.settings.scrollH = (int)(((float)(menu->scroll_grab.y - minScrollY) / (float)(maxScrollY - minScrollY)) * 1600.0f);
    return (1);
}

static int handle_resolution_click(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas)
{
    SDL_Rect mouseCoords = {MouseDatas->x - (game->window->w - menu->ViewPortCoords.w) / 2, MouseDatas->y - menu->ViewPortCoords.y, 0, 0};
    SDL_Rect ButtonsCoords;

    for (int i = 0; i < 3; i++)
    {
        ButtonsCoords = menu->resolutionBtnsCoords[i];
        to_responsive(game->window, &ButtonsCoords);
        if (is_mouse_pos_inside_button(mouseCoords, ButtonsCoords))
        {
            ft_printf("Clicked resolution %d\n", i);
            switch (i)
            {
            case 0:
                SDL_SetWindowSize(game->window->winPTR, 1280, 720);
                game->window->w = 1280;
                game->window->h = 720;
                break;
            case 1:
                SDL_SetWindowSize(game->window->winPTR, 1920, 1080);
                game->window->w = 1920;
                game->window->h = 1080;
                break;
            case 2:
                SDL_SetWindowSize(game->window->winPTR, 2560, 1440);
                game->window->w = 2560;
                game->window->h = 1440;
                break;
            default:
                break;
            }
            return (1);
        }
    }
    return (0);
}

static int handle_display_mode_click(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas)
{
    SDL_Rect mouseCoords = {MouseDatas->x - (game->window->w - menu->ViewPortCoords.w) / 2, MouseDatas->y - menu->ViewPortCoords.y, 0, 0};
    SDL_Rect ButtonsCoords;

    for (int i = 3; i < 6; i++)
    {
        ButtonsCoords = menu->resolutionBtnsCoords[i];
        to_responsive(game->window, &ButtonsCoords);
        if (is_mouse_pos_inside_button(mouseCoords, ButtonsCoords))
        {
            Uint32 flags = SDL_GetWindowFlags(game->window->winPTR);

            switch (i)
            {
            case 3:
                if (!(flags & SDL_WINDOW_FULLSCREEN) && !(flags & SDL_WINDOW_FULLSCREEN_DESKTOP))
                    get_screen_size(&game->window->w, &game->window->h);
                SDL_SetWindowFullscreen(game->window->winPTR, SDL_WINDOW_FULLSCREEN);
                break;
            case 4:
                if (!(flags & SDL_WINDOW_FULLSCREEN) && !(flags & SDL_WINDOW_FULLSCREEN_DESKTOP))
                    get_screen_size(&game->window->w, &game->window->h);
                SDL_SetWindowFullscreen(game->window->winPTR, SDL_WINDOW_FULLSCREEN_DESKTOP);
                break;
            case 5:
                if (SDL_SetWindowFullscreen(game->window->winPTR, 0) != 0)
                    return (1);
                SDL_Delay(50);
                SDL_SetWindowSize(game->window->winPTR, 1920, 1080);
                game->window->w = 1920;
                game->window->h = 1080;
                break;
            default:
                break;
            }
            return (1);
        }
    }
    return (0);
}

void handle_settings_click(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click)
{
    if (grab_fov(game, menu, MouseDatas, click))
        return;
    if (grab_scroll(game, menu, MouseDatas, click))
        return;
    if (handle_language_selection(game, menu, MouseDatas, click))
        return;
    if (click && handle_click_control(game, menu, MouseDatas))
        return;
    if (click && handle_resolution_click(game, menu, MouseDatas))
        return;
    if (click && handle_display_mode_click(game, menu, MouseDatas))
        return;
}

void handle_settings_released(t_settings_menu *menu)
{
    if (menu->isGrabbingSlider)
    {
        menu->isGrabbingSlider = 0;
        return;
    }

    if (menu->isGrabbingScrollBar)
    {
        menu->isGrabbingScrollBar = 0;
        return;
    }
}