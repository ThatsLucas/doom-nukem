/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:12:36 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/21 18:33:17 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

void draw_texture(int x, int y, int w, int h, t_WIN *win, SDL_Texture *texture)
{
    SDL_Rect dest = { x, y, w, h };
    to_responsive(win, &dest);
    SDL_RenderCopy(win->renderPTR, texture, NULL, &dest);
}

int draw_languages(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;
    int separatorW = menu->separator.w / 1.8;
    int separatorH = menu->separator.h / 1.8;

    yPos += 150;
    draw_texture((1044 - menu->separator.w / 1.8) / 2, yPos - *scrollH, separatorW, separatorH, win, menu->separator.texture);
    yPos += separatorH + 20;
    draw_texture((1044 - menu->texts[4].w) / 2, yPos + 25 - *scrollH, menu->texts[4].w, menu->texts[4].h, win, menu->texts[4].texture);
    yPos += menu->texts[4].h + 20;

    int languageXOffset = (1044 - (20*3 + (menu->languages[0].w/9 * 4)))/ 2;
    draw_texture(languageXOffset, yPos + 25 - *scrollH, menu->languages[0].w/9, menu->languages[0].h/9, win, menu->languages[0].texture);
    languageXOffset += menu->languages[0].w/9 + 20;

    draw_texture(languageXOffset, yPos + 25 - *scrollH, menu->languages[1].w/9, menu->languages[1].h/9, win, menu->languages[1].texture);
    languageXOffset += menu->languages[1].w/9 + 20;

    draw_texture(languageXOffset, yPos + 25 - *scrollH, menu->languages[2].w/9, menu->languages[2].h/9, win, menu->languages[2].texture);
    languageXOffset += menu->languages[2].w/9 + 20;

    draw_texture(languageXOffset, yPos + 25 - *scrollH, menu->languages[3].w/9, menu->languages[3].h/9, win, menu->languages[3].texture);
    languageXOffset += menu->languages[3].w/9 + 20;
    
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
        create_text(&fovText, win->renderPTR, fovSTR, "assets/fonts/AmazDooMLeft.ttf");
        free(fovSTR);
        draw_texture((1044 - fovText.w) / 2, yPos - *scrollH, fovText.w, fovText.h, win, fovText.texture);
        SDL_DestroyTexture(fovText.texture);
    }

    yPos += 60;
    draw_texture((1044 - menu->slider_bar.w/2) / 2, yPos - *scrollH, menu->slider_bar.w/2, menu->slider_bar.h/2, win, menu->slider_bar.texture);
    menu->slider_grab.y = yPos - *scrollH + ((menu->slider_bar.h/2 - menu->slider_grab.h/6) / 2);
    draw_texture(menu->slider_grab.x, menu->slider_grab.y, menu->slider_grab.w/6, menu->slider_grab.h/6, win, menu->slider_grab.texture);
    return (yPos);
}

int draw_controls(int *scrollH, t_WIN *win, t_settings_menu *menu)
{
    int keyW = menu->keys.w / 8;
    int keyH = menu->keys.h / 8;
    int xPos = (730 - keyW) / 2;
    int yPos = 0;

    draw_texture(xPos, yPos - *scrollH, keyW, keyH, win, menu->keys.texture);
    draw_texture(xPos + keyW + 40, yPos - *scrollH + (keyH - menu->texts[1].h + 20) / 2, menu->texts[1].w, menu->texts[1].h, win, menu->texts[1].texture);
    yPos += keyH + 20;
    draw_texture(xPos, yPos - *scrollH, keyW, keyH, win, menu->keys.texture);
    draw_texture(xPos + keyW + 40, yPos - *scrollH + (keyH - menu->texts[2].h + 20) / 2, menu->texts[2].w, menu->texts[2].h, win, menu->texts[2].texture);
    yPos += keyH + 20;
    draw_texture(xPos, yPos - *scrollH, keyW, keyH, win, menu->keys.texture);
    draw_texture(xPos + keyW + 40, yPos - *scrollH + (keyH - menu->texts[2].h + 20) / 2, menu->texts[2].w, menu->texts[2].h, win, menu->texts[2].texture);
    yPos += keyH + 20;
    draw_texture(xPos, yPos - *scrollH, keyW, keyH, win, menu->keys.texture);
    draw_texture(xPos + keyW + 40, yPos - *scrollH + (keyH - menu->texts[2].h + 20) / 2, menu->texts[2].w, menu->texts[2].h, win, menu->texts[2].texture);

    return (yPos);
}

void    draw_scroll_bar(t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;

    draw_texture(1890 - menu->scroll.w / 5, 20, menu->scroll.w / 5, 1040, win, menu->scroll.texture);
    draw_texture(1890 - menu->scroll.w / 5 + (menu->scroll.w/5 - menu->scroll_grab.w/14) / 2, menu->scroll_grab.y, menu->scroll_grab.w/14, menu->scroll_grab.h/14, win, menu->scroll_grab.texture);
}