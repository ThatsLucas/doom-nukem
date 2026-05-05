/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:12:36 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/23 12:06:28 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

void draw_pick_a_key(t_WIN *win)
{
    SDL_Rect coords = {0, 0, 1920, 1080};
    to_responsive(win, &coords);

    t_RGB black = {0, 0, 0, 200};
    create_rectangle(win->renderPTR, coords, black);
    draw_texture((1920 - win->menus.settings.texts[13].w) / 2, (1080 - win->menus.settings.texts[13].h) / 2,
                 win->menus.settings.texts[13].w, win->menus.settings.texts[13].h, win, win->menus.settings.texts[13].texture);
}

void draw_texture(int x, int y, int w, int h, t_WIN *win, SDL_Texture *texture)
{
    SDL_Rect dest = {x, y, w, h};
    to_responsive(win, &dest);
    SDL_RenderCopy(win->renderPTR, texture, NULL, &dest);
}

int draw_display_mode(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;
    int separatorW = menu->separator.w / 1.8;
    int separatorH = menu->separator.h / 1.8;

    yPos += 150;
    draw_texture((1044 - menu->separator.w / 1.8) / 2, yPos - *scrollH, separatorW, separatorH, win, menu->separator.texture);
    yPos += separatorH + 20;
    draw_texture((1044 - menu->texts[18].w) / 2, yPos + 25 - *scrollH, menu->texts[18].w, menu->texts[18].h, win, menu->texts[18].texture);
    yPos += menu->texts[18].h + 20;

    draw_texture(0, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture((1044 - win->menus.main.button.w / 5) / 2, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture(1044 - win->menus.main.button.w / 5, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    menu->resolutionBtnsCoords[3] = (SDL_Rect){0, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    menu->resolutionBtnsCoords[4] = (SDL_Rect){(1044 - win->menus.main.button.w / 5) / 2, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    menu->resolutionBtnsCoords[5] = (SDL_Rect){1044 - win->menus.main.button.w / 5, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    draw_texture((win->menus.main.button.w / 5 - menu->texts[19].w) / 2, yPos - *scrollH + 15 + (win->menus.main.button.h / 5 - menu->texts[19].h) / 2, menu->texts[19].w, menu->texts[19].h, win, menu->texts[19].texture);
    draw_texture((1044 - win->menus.main.button.w / 5) / 2 + (win->menus.main.button.w / 5 - menu->texts[20].w) / 2, yPos - *scrollH + 15 + (win->menus.main.button.h / 5 - menu->texts[20].h) / 2, menu->texts[20].w, menu->texts[20].h, win, menu->texts[20].texture);
    draw_texture(1044 - win->menus.main.button.w / 5 + (win->menus.main.button.w / 5 - menu->texts[21].w) / 2, yPos - *scrollH + 15 + (win->menus.main.button.h / 5 - menu->texts[21].h) / 2, menu->texts[21].w, menu->texts[21].h, win, menu->texts[21].texture);

    return (yPos);
}

int draw_mouse_sensibility(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;
    int separatorW = menu->separator.w / 1.8;
    int separatorH = menu->separator.h / 1.8;

    yPos += 150;
    draw_texture((1044 - menu->separator.w / 1.8) / 2, yPos - *scrollH, separatorW, separatorH, win, menu->separator.texture);
    yPos += separatorH + 20;
    draw_texture((1044 - menu->texts[22].w) / 2, yPos + 25 - *scrollH, menu->texts[22].w, menu->texts[22].h, win, menu->texts[22].texture);
    yPos += menu->texts[22].h + 20;

    t_font mouse_sensi;
    mouse_sensi.color = (SDL_Color){255, 255, 255, 255};
    mouse_sensi.size = 60;
    char *MouseSensiSTR = ft_itoa(game->settings.MouseSensibility * 100000);
    if (MouseSensiSTR)
    {
        create_text(&mouse_sensi, win->renderPTR, MouseSensiSTR, DNFONT);
        free(MouseSensiSTR);
        draw_texture((1044 - mouse_sensi.w) / 2, yPos - *scrollH, mouse_sensi.w, mouse_sensi.h, win, mouse_sensi.texture);
        SDL_DestroyTexture(mouse_sensi.texture);
    }

    yPos += 60;
    draw_texture((1044 - menu->slider_bar.w / 2) / 2, yPos - *scrollH, menu->slider_bar.w / 2, menu->slider_bar.h / 2, win, menu->slider_bar.texture);

    SDL_Rect OldCoords = menu->MouseSensiCoords;
    menu->MouseSensiCoords = (SDL_Rect){OldCoords.x, yPos - *scrollH + ((menu->slider_bar.h / 2 - menu->slider_grab.h / 6) / 2), OldCoords.w, OldCoords.h};
    draw_texture(menu->MouseSensiCoords.x, menu->MouseSensiCoords.y, menu->MouseSensiCoords.w, menu->MouseSensiCoords.h, win, menu->slider_grab.texture);

    return (yPos);
}

int draw_resolution(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;
    int separatorW = menu->separator.w / 1.8;
    int separatorH = menu->separator.h / 1.8;

    yPos += 150;
    draw_texture((1044 - menu->separator.w / 1.8) / 2, yPos - *scrollH, separatorW, separatorH, win, menu->separator.texture);
    yPos += separatorH + 20;
    draw_texture((1044 - menu->texts[14].w) / 2, yPos + 25 - *scrollH, menu->texts[14].w, menu->texts[14].h, win, menu->texts[14].texture);
    yPos += menu->texts[14].h + 20;

    draw_texture(0, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture((1044 - win->menus.main.button.w / 5) / 2, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture(1044 - win->menus.main.button.w / 5, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    menu->resolutionBtnsCoords[0] = (SDL_Rect){0, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    menu->resolutionBtnsCoords[1] = (SDL_Rect){(1044 - win->menus.main.button.w / 5) / 2, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    menu->resolutionBtnsCoords[2] = (SDL_Rect){1044 - win->menus.main.button.w / 5, yPos - *scrollH, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    draw_texture((win->menus.main.button.w / 5 - menu->texts[15].w) / 2, yPos - *scrollH + 10 + (win->menus.main.button.h / 5 - menu->texts[15].h) / 2, menu->texts[15].w, menu->texts[15].h, win, menu->texts[15].texture);
    draw_texture((1044 - win->menus.main.button.w / 5) / 2 + (win->menus.main.button.w / 5 - menu->texts[16].w) / 2, yPos - *scrollH + 10 + (win->menus.main.button.h / 5 - menu->texts[16].h) / 2, menu->texts[16].w, menu->texts[16].h, win, menu->texts[16].texture);
    draw_texture(1044 - win->menus.main.button.w / 5 + (win->menus.main.button.w / 5 - menu->texts[17].w) / 2, yPos - *scrollH + 10 + (win->menus.main.button.h / 5 - menu->texts[17].h) / 2, menu->texts[17].w, menu->texts[17].h, win, menu->texts[17].texture);

    return (yPos);
}

int draw_languages(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;
    int separatorW = menu->separator.w / 1.8;
    int separatorH = menu->separator.h / 1.8;
    int languageXOffset;
    int languagePos[4];
    int selectedIdx;
    int selectedW;
    int selectedH;
    int selectedX;

    yPos += 150;
    draw_texture((1044 - menu->separator.w / 1.8) / 2, yPos - *scrollH, separatorW, separatorH, win, menu->separator.texture);
    yPos += separatorH + 20;
    draw_texture((1044 - menu->texts[4].w) / 2, yPos + 25 - *scrollH, menu->texts[4].w, menu->texts[4].h, win, menu->texts[4].texture);
    yPos += menu->texts[4].h + 20;

    languageXOffset = (1044 - (20 * 3 + (menu->languages[0].w / 9 * 4))) / 2;
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
    draw_texture(selectedX, yPos + 12 - *scrollH, selectedW, selectedH, win,
                 menu->languages[4].texture);

    menu->languagesCoords[0] = (SDL_Rect){languageXOffset, yPos + 25 - *scrollH, menu->languages[0].w / 9, menu->languages[0].h / 9};
    draw_texture(menu->languagesCoords[0].x, menu->languagesCoords[0].y, menu->languagesCoords[0].w, menu->languagesCoords[0].h, win, menu->languages[0].texture);
    languageXOffset += menu->languages[0].w / 9 + 20;

    menu->languagesCoords[1] = (SDL_Rect){languageXOffset, yPos + 25 - *scrollH, menu->languages[1].w / 9, menu->languages[1].h / 9};
    draw_texture(menu->languagesCoords[1].x, menu->languagesCoords[1].y, menu->languagesCoords[1].w, menu->languagesCoords[1].h, win, menu->languages[1].texture);
    languageXOffset += menu->languages[1].w / 9 + 20;

    menu->languagesCoords[2] = (SDL_Rect){languageXOffset, yPos + 25 - *scrollH, menu->languages[2].w / 9, menu->languages[2].h / 9};
    draw_texture(menu->languagesCoords[2].x, menu->languagesCoords[2].y, menu->languagesCoords[2].w, menu->languagesCoords[2].h, win, menu->languages[2].texture);
    languageXOffset += menu->languages[2].w / 9 + 20;

    menu->languagesCoords[3] = (SDL_Rect){languageXOffset, yPos + 25 - *scrollH, menu->languages[3].w / 9, menu->languages[3].h / 9};
    draw_texture(menu->languagesCoords[3].x, menu->languagesCoords[3].y, menu->languagesCoords[3].w, menu->languagesCoords[3].h, win, menu->languages[3].texture);
    languageXOffset += menu->languages[3].w / 9 + 20;

    return (yPos);
}

int draw_FOV(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;
    int separatorW = menu->separator.w / 1.8;
    int separatorH = menu->separator.h / 1.8;

    yPos += 150;
    draw_texture((1044 - menu->separator.w / 1.8) / 2, yPos - *scrollH, separatorW, separatorH, win, menu->separator.texture);
    yPos += separatorH + 20;
    draw_texture((1044 - menu->texts[3].w) / 2, yPos + 25 - *scrollH, menu->texts[3].w, menu->texts[3].h, win, menu->texts[3].texture);
    yPos += menu->texts[3].h + 20;

    t_font fovText;
    fovText.color = (SDL_Color){255, 255, 255, 255};
    fovText.size = 60;
    char *fovSTR = ft_itoa(game->settings.FOV * 100);
    if (fovSTR)
    {
        create_text(&fovText, win->renderPTR, fovSTR, DNFONT);
        free(fovSTR);
        draw_texture((1044 - fovText.w) / 2, yPos - *scrollH, fovText.w, fovText.h, win, fovText.texture);
        SDL_DestroyTexture(fovText.texture);
    }

    yPos += 60;
    draw_texture((1044 - menu->slider_bar.w / 2) / 2, yPos - *scrollH, menu->slider_bar.w / 2, menu->slider_bar.h / 2, win, menu->slider_bar.texture);
    menu->slider_grab.y = yPos - *scrollH + ((menu->slider_bar.h / 2 - menu->slider_grab.h / 6) / 2);
    draw_texture(menu->slider_grab.x, menu->slider_grab.y, menu->slider_grab.w / 6, menu->slider_grab.h / 6, win, menu->slider_grab.texture);
    return (yPos);
}

int draw_controls(int *scrollH, t_WIN *win, t_settings_menu *menu)
{
    int keyW = menu->keys.w / 8;
    int keyH = menu->keys.h / 8;
    int xPos = (730 - keyW) / 2;
    int yPos = 0;

    draw_texture(xPos, yPos - *scrollH, keyW, keyH, win, menu->keys.texture);
    menu->keysCoords[0] = (SDL_Rect){xPos, yPos - *scrollH, keyW, keyH};
    draw_texture(xPos + keyW + 40, yPos - *scrollH + (keyH - menu->texts[1].h + 20) / 2, menu->texts[1].w, menu->texts[1].h, win, menu->texts[1].texture);
    draw_texture(xPos + ((keyW - menu->texts[9].w) / 2), yPos - *scrollH + (keyH - menu->texts[9].h + 35) / 2, menu->texts[9].w, menu->texts[9].h, win, menu->texts[9].texture);
    yPos += keyH + 20;
    draw_texture(xPos, yPos - *scrollH, keyW, keyH, win, menu->keys.texture);
    menu->keysCoords[1] = (SDL_Rect){xPos, yPos - *scrollH, keyW, keyH};
    draw_texture(xPos + keyW + 40, yPos - *scrollH + (keyH - menu->texts[2].h + 20) / 2, menu->texts[2].w, menu->texts[2].h, win, menu->texts[2].texture);
    draw_texture(xPos + ((keyW - menu->texts[10].w) / 2), yPos - *scrollH + (keyH - menu->texts[10].h + 35) / 2, menu->texts[10].w, menu->texts[10].h, win, menu->texts[10].texture);
    yPos += keyH + 20;
    draw_texture(xPos, yPos - *scrollH, keyW, keyH, win, menu->keys.texture);
    menu->keysCoords[2] = (SDL_Rect){xPos, yPos - *scrollH, keyW, keyH};
    draw_texture(xPos + keyW + 40, yPos - *scrollH + (keyH - menu->texts[7].h + 20) / 2, menu->texts[7].w, menu->texts[7].h, win, menu->texts[7].texture);
    draw_texture(xPos + ((keyW - menu->texts[11].w) / 2), yPos - *scrollH + (keyH - menu->texts[11].h + 35) / 2, menu->texts[11].w, menu->texts[11].h, win, menu->texts[11].texture);
    yPos += keyH + 20;
    draw_texture(xPos, yPos - *scrollH, keyW, keyH, win, menu->keys.texture);
    menu->keysCoords[3] = (SDL_Rect){xPos, yPos - *scrollH, keyW, keyH};
    draw_texture(xPos + keyW + 40, yPos - *scrollH + (keyH - menu->texts[8].h + 20) / 2, menu->texts[8].w, menu->texts[8].h, win, menu->texts[8].texture);
    draw_texture(xPos + ((keyW - menu->texts[12].w) / 2), yPos - *scrollH + (keyH - menu->texts[12].h + 35) / 2, menu->texts[12].w, menu->texts[12].h, win, menu->texts[12].texture);

    return (yPos);
}

void draw_scroll_bar(t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;

    draw_texture(1890 - menu->scroll.w / 5, 20, menu->scroll.w / 5, 1040, win, menu->scroll.texture);
    draw_texture(1890 - menu->scroll.w / 5 + (menu->scroll.w / 5 - menu->scroll_grab.w / 14) / 2, menu->scroll_grab.y, menu->scroll_grab.w / 14, menu->scroll_grab.h / 14, win, menu->scroll_grab.texture);
}