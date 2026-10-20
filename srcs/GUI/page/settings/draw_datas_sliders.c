/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_datas_sliders.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:12:00 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:12:00 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

/* Value of a slider (FOV, sensibility), centered */
static void draw_slider_value(t_WIN *win, int value, int y)
{
    t_font text;
    char *str = ft_itoa(value);

    text.color = (SDL_Color){255, 255, 255, 255};
    text.size = 60;
    if (str)
    {
        create_text(&text, win->renderPTR, str, DNFONT);
        free(str);
        draw_texture((1044 - text.w) / 2, y, text.w, text.h, win, text.texture);
        SDL_DestroyTexture(text.texture);
    }
}

int draw_mouse_sensibility(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;

    yPos = draw_section_header(yPos, scrollH, win, &menu->texts[22]);
    draw_slider_value(win, game->settings.MouseSensibility * 100000, yPos - *scrollH);

    yPos += 60;
    draw_texture((1044 - menu->slider_bar.w / 2) / 2, yPos - *scrollH, menu->slider_bar.w / 2, menu->slider_bar.h / 2, win, menu->slider_bar.texture);

    SDL_Rect OldCoords = menu->MouseSensiCoords;
    menu->MouseSensiCoords = (SDL_Rect){OldCoords.x, yPos - *scrollH + ((menu->slider_bar.h / 2 - menu->slider_grab.h / 6) / 2), OldCoords.w, OldCoords.h};
    draw_texture(menu->MouseSensiCoords.x, menu->MouseSensiCoords.y, menu->MouseSensiCoords.w, menu->MouseSensiCoords.h, win, menu->slider_grab.texture);

    return (yPos);
}

int draw_FOV(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;

    yPos = draw_section_header(yPos, scrollH, win, &menu->texts[3]);
    draw_slider_value(win, game->settings.FOV * 100, yPos - *scrollH);

    yPos += 60;
    draw_texture((1044 - menu->slider_bar.w / 2) / 2, yPos - *scrollH, menu->slider_bar.w / 2, menu->slider_bar.h / 2, win, menu->slider_bar.texture);
    menu->slider_grab.y = yPos - *scrollH + ((menu->slider_bar.h / 2 - menu->slider_grab.h / 6) / 2);
    draw_texture(menu->slider_grab.x, menu->slider_grab.y, menu->slider_grab.w / 6, menu->slider_grab.h / 6, win, menu->slider_grab.texture);
    return (yPos);
}
