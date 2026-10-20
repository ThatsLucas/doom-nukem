/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs_buttons.c                            :+:      :+:    :+:   */
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

int handle_language_selection(t_game *game, t_settings_menu *menu,
                                     SDL_MouseMotionEvent *MouseDatas, int click)
{
    SDL_Rect mouseCoords;

    if (!click)
        return (0);
    mouseCoords.x = MouseDatas->x - (game->window->w - menu->ViewPortCoords.w) / 2;
    mouseCoords.y = MouseDatas->y - menu->ViewPortCoords.y;
    mouseCoords.w = 0;
    mouseCoords.h = 0;
    if (mouseCoords.x < 0 || mouseCoords.x > menu->ViewPortCoords.w || mouseCoords.y < 0 || mouseCoords.y > menu->ViewPortCoords.h)
        return (0);

    for (int i = 0; i < 4; i++)
    {
        SDL_Rect languageCoords = menu->languagesCoords[i];
        if (is_mouse_pos_inside_button(mouseCoords, languageCoords))
        {
            if (game->selected_language == i)
                return (1);
            game->selected_language = i;
            free_languages(game);
            parse_languages(game, i);
            refresh_main_menu_texts(game);
            refresh_settings_texts(game, menu);
            refresh_lobby_texts(game);
            refresh_cinematics_texts(game);
            refresh_pause_menu_texts(game);
            return (1);
        }
    }
    return (0);
}

int handle_click_control(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas)
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

static void set_window_resolution(t_game *game, int w, int h)
{
    SDL_SetWindowSize(game->window->winPTR, w, h);
    game->window->w = w;
    game->window->h = h;
}

int handle_resolution_click(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas)
{
    SDL_Rect mouseCoords = {MouseDatas->x - (game->window->w - menu->ViewPortCoords.w) / 2, MouseDatas->y - menu->ViewPortCoords.y, 0, 0};
    SDL_Rect ButtonsCoords;

    for (int i = 0; i < 3; i++)
    {
        ButtonsCoords = menu->resolutionBtnsCoords[i];
        to_responsive(game->window, &ButtonsCoords);
        if (is_mouse_pos_inside_button(mouseCoords, ButtonsCoords))
        {
            if (i == 0)
                set_window_resolution(game, 1280, 720);
            else if (i == 1)
                set_window_resolution(game, 1920, 1080);
            else if (i == 2)
                set_window_resolution(game, 2560, 1440);
            return (1);
        }
    }
    return (0);
}

/* mode: 3 fullscreen, 4 borderless, 5 windowed */
static void set_display_mode(t_game *game, int mode)
{
    Uint32 flags = SDL_GetWindowFlags(game->window->winPTR);

    if (mode == 3 || mode == 4)
    {
        if (!(flags & SDL_WINDOW_FULLSCREEN) && !(flags & SDL_WINDOW_FULLSCREEN_DESKTOP))
            get_screen_size(&game->window->w, &game->window->h);
        if (mode == 3)
            SDL_SetWindowFullscreen(game->window->winPTR, SDL_WINDOW_FULLSCREEN);
        else
            SDL_SetWindowFullscreen(game->window->winPTR, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    else if (mode == 5)
    {
        if (SDL_SetWindowFullscreen(game->window->winPTR, 0) != 0)
            return ;
        SDL_Delay(50);
        set_window_resolution(game, 1920, 1080);
    }
}

int handle_display_mode_click(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas)
{
    SDL_Rect mouseCoords = {MouseDatas->x - (game->window->w - menu->ViewPortCoords.w) / 2, MouseDatas->y - menu->ViewPortCoords.y, 0, 0};
    SDL_Rect ButtonsCoords;

    for (int i = 3; i < 6; i++)
    {
        ButtonsCoords = menu->resolutionBtnsCoords[i];
        to_responsive(game->window, &ButtonsCoords);
        if (is_mouse_pos_inside_button(mouseCoords, ButtonsCoords))
        {
            set_display_mode(game, i);
            return (1);
        }
    }
    return (0);
}
