/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:22:22 by lucas             #+#    #+#             */
/*   Updated: 2026/07/06 15:17:16 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

/* Scrollable part of the settings, drawn inside the viewport dest */
static void draw_settings_viewport(t_game *game, t_settings_menu *menu, SDL_Rect *dest)
{
    SDL_Renderer *renderer = game->window->renderPTR;
    int yPos = 0;

    SDL_RenderSetViewport(renderer, dest);
    yPos = draw_controls(&menu->scrollH, game->window, menu);
    yPos = draw_FOV(yPos, &menu->scrollH, game, menu);
    yPos = draw_mouse_sensibility(yPos, &menu->scrollH, game, menu);
    yPos = draw_languages(yPos, &menu->scrollH, game, menu);
    yPos = draw_resolution(yPos, &menu->scrollH, game, menu);
    yPos = draw_display_mode(yPos, &menu->scrollH, game, menu);

    SDL_RenderSetViewport(renderer, NULL);
}

void draw_settings_menu(t_game *game)
{
    t_WIN *win = game->window;
    t_settings_menu *menu = &win->menus.settings;
    int viewportX = (1920 - 1044) / 2;

    game->window->menus.current = 2;

    draw_texture(0, 0, 1920, 1080, win, menu->background.texture);
    draw_texture((1920 - menu->texts[0].w) / 2, 15, menu->texts[0].w, menu->texts[0].h, win, menu->texts[0].texture);
    draw_scroll_bar(game, menu);

    /*Viewport*/
    SDL_Rect dest = {viewportX, 136, 1044, 842};
    to_responsive(win, &dest);
    menu->ViewPortCoords = dest;

    draw_settings_viewport(game, menu, &dest);
    /*Viewport END*/
    draw_texture(20, 20, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);

    if (menu->is_selecting_control > 0)
        draw_pick_a_key(win);
    else
        display_buttons(game->window->buttonList, game, 2);
    if (game->is_paused)
    {
        draw_texture(20, 20, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
        draw_texture(10 + game->window->menus.pause.texts[0].w / 2, 30, game->window->menus.pause.texts[0].w/2, game->window->menus.pause.texts[0].h/2, win, game->window->menus.pause.texts[0].texture);
    }

}
