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

/* Saves the new key of a control and updates its text */
static void set_control_key(t_game *game, int *setting, t_font *text, int key)
{
    *setting = key;
    destroy_text_texture(text);
    create_text(text, game->window->renderPTR, (char *)SDL_GetKeyName(key),
                DNFONT);
}

int handle_key_control_selected(t_game *game, int key)
{
    t_settings_menu *menu = &game->window->menus.settings;

    if (game->window->menus.current != 2)
        return (0);

    int controlAsked = menu->is_selecting_control;

    if (controlAsked == 1)
        set_control_key(game, &game->settings.move_forward, &menu->texts[9], key);
    else if (controlAsked == 2)
        set_control_key(game, &game->settings.move_backward, &menu->texts[10], key);
    else if (controlAsked == 3)
        set_control_key(game, &game->settings.move_left, &menu->texts[11], key);
    else if (controlAsked == 4)
        set_control_key(game, &game->settings.move_right, &menu->texts[12], key);

    menu->is_selecting_control = 0;
    return (1);
}

void handle_settings_click(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click)
{
    if (grab_fov(game, menu, MouseDatas, click))
        return;
    if (grab_scroll(game, menu, MouseDatas, click))
        return;
    if (grab_mouse_sensibility(game, menu, MouseDatas, click))
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

    if (menu->isGrabbingSliderMouseSensi)
    {
        menu->isGrabbingSliderMouseSensi = 0;
        return;
    }

    if (menu->isGrabbingScrollBar)
    {
        menu->isGrabbingScrollBar = 0;
        return;
    }
}