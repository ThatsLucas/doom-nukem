/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_datas_choices.c                               :+:      :+:    :+:   */
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

/*
	Three buttons on a row (left, center, right) with their labels.
	first: index of the first button coords / text, text_dy: label vertical offset
*/
static void draw_three_buttons(t_WIN *win, int y, int first_coord, int first_text, int text_dy)
{
    t_settings_menu *menu = &win->menus.settings;
    int bw = win->menus.main.button.w / 5;
    int bh = win->menus.main.button.h / 5;
    int xs[3] = {0, (1044 - bw) / 2, 1044 - bw};
    t_font *text;

    for (int i = 0; i < 3; i++)
        draw_texture(xs[i], y, bw, bh, win, win->menus.main.button.texture);
    for (int i = 0; i < 3; i++)
        menu->resolutionBtnsCoords[first_coord + i] = (SDL_Rect){xs[i], y, bw, bh};
    for (int i = 0; i < 3; i++)
    {
        text = &menu->texts[first_text + i];
        draw_texture(xs[i] + (bw - text->w) / 2, y + text_dy + (bh - text->h) / 2, text->w, text->h, win, text->texture);
    }
}

int draw_display_mode(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    yPos = draw_section_header(yPos, scrollH, game->window, &menu->texts[18]);
    draw_three_buttons(game->window, yPos - *scrollH, 3, 19, 15);
    return (yPos);
}

int draw_resolution(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    yPos = draw_section_header(yPos, scrollH, game->window, &menu->texts[14]);
    draw_three_buttons(game->window, yPos - *scrollH, 0, 15, 10);
    return (yPos);
}

/* Frame drawn behind the selected language flag */
static void draw_selected_language(t_game *game, t_settings_menu *menu, int languageXOffset, int y)
{
    int languagePos[4];
    int selectedIdx;
    int selectedW;
    int selectedH;
    int selectedX;

    selectedIdx = game->selected_language;
    if (selectedIdx < 0)
        selectedIdx = 0;
    if (selectedIdx > 3)
        selectedIdx = 3;
    selectedW = menu->languages[4].w / 7.5;
    selectedH = menu->languages[4].h / 7.5;

    languagePos[0] = languageXOffset;
    languagePos[1] = languagePos[0] + (menu->languages[0].w / 9) + 20;
    languagePos[2] = languagePos[1] + (menu->languages[1].w / 9) + 20;
    languagePos[3] = languagePos[2] + (menu->languages[2].w / 9) + 20;
    selectedX = languagePos[selectedIdx] + ((menu->languages[selectedIdx].w / 9) - selectedW) / 2;
    draw_texture(selectedX, y, selectedW, selectedH, game->window,
                 menu->languages[4].texture);
}

int draw_languages(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;
    int languageXOffset;

    yPos = draw_section_header(yPos, scrollH, win, &menu->texts[4]);

    languageXOffset = (1044 - (20 * 3 + (menu->languages[0].w / 9 * 4))) / 2;
    draw_selected_language(game, menu, languageXOffset, yPos + 12 - *scrollH);

    for (int i = 0; i < 4; i++)
    {
        menu->languagesCoords[i] = (SDL_Rect){languageXOffset, yPos + 25 - *scrollH, menu->languages[i].w / 9, menu->languages[i].h / 9};
        draw_texture(menu->languagesCoords[i].x, menu->languagesCoords[i].y, menu->languagesCoords[i].w, menu->languagesCoords[i].h, win, menu->languages[i].texture);
        languageXOffset += menu->languages[i].w / 9 + 20;
    }

    return (yPos);
}
