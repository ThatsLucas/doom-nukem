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

/* Separator + title of a settings section, returns the y below the title */
int draw_section_header(int yPos, int *scrollH, t_WIN *win, t_font *title)
{
    t_settings_menu *menu = &win->menus.settings;
    int separatorW = menu->separator.w / 1.8;
    int separatorH = menu->separator.h / 1.8;

    yPos += 150;
    draw_texture((1044 - menu->separator.w / 1.8) / 2, yPos - *scrollH, separatorW, separatorH, win, menu->separator.texture);
    yPos += separatorH + 20;
    draw_texture((1044 - title->w) / 2, yPos + 25 - *scrollH, title->w, title->h, win, title->texture);
    yPos += title->h + 20;
    return (yPos);
}

/* One control: key image, action label and key name */
static void draw_control_row(t_WIN *win, int y, t_font *label, t_font *key)
{
    t_settings_menu *menu = &win->menus.settings;
    int keyW = menu->keys.w / 8;
    int keyH = menu->keys.h / 8;
    int xPos = (730 - keyW) / 2;

    draw_texture(xPos, y, keyW, keyH, win, menu->keys.texture);
    draw_texture(xPos + keyW + 40, y + (keyH - label->h + 20) / 2, label->w, label->h, win, label->texture);
    draw_texture(xPos + ((keyW - key->w) / 2), y + (keyH - key->h + 35) / 2, key->w, key->h, win, key->texture);
}

int draw_controls(int *scrollH, t_WIN *win, t_settings_menu *menu)
{
    int keyW = menu->keys.w / 8;
    int keyH = menu->keys.h / 8;
    int xPos = (730 - keyW) / 2;
    int yPos = 0;
    int labels[4] = {1, 2, 7, 8};

    for (int i = 0; i < 4; i++)
    {
        if (i > 0)
            yPos += keyH + 20;
        menu->keysCoords[i] = (SDL_Rect){xPos, yPos - *scrollH, keyW, keyH};
        draw_control_row(win, yPos - *scrollH, &menu->texts[labels[i]], &menu->texts[9 + i]);
    }
    return (yPos);
}

void draw_scroll_bar(t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;

    draw_texture(1890 - menu->scroll.w / 5, 20, menu->scroll.w / 5, 1040, win, menu->scroll.texture);
    draw_texture(1890 - menu->scroll.w / 5 + (menu->scroll.w / 5 - menu->scroll_grab.w / 14) / 2, menu->scroll_grab.y, menu->scroll_grab.w / 14, menu->scroll_grab.h / 14, win, menu->scroll_grab.texture);
}