/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:22:22 by lucas             #+#    #+#             */
/*   Updated: 2026/04/21 15:59:10 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

static void *init_texts(void *window)
{
    t_WIN *win = (t_WIN *)window;
    SDL_Renderer *renderer = win->renderPTR;
    t_settings_menu *menu = &win->menus.settings;
    menu->texts[0].size = 80;
    menu->texts[0].color = (SDL_Color){255, 255, 255, 255};
    create_text(&menu->texts[0], renderer, "SETTINGS", "assets/fonts/AmazDooMLeft.ttf");
    menu->texts[1].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[1].size = 50;
    create_text(&menu->texts[1], renderer, "- Move forward", "assets/fonts/AmazDooMLeft.ttf");

    menu->texts[2].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[2].size = 50;
    create_text(&menu->texts[2], renderer, "- Move backward", "assets/fonts/AmazDooMLeft.ttf");

    menu->texts[3].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[3].size = 80;
    create_text(&menu->texts[3], renderer, "FOV", "assets/fonts/AmazDooMLeft.ttf");

    // int scrollH = 136;
    // SDL_Rect dest = { (1920 - menu->keys.w / 2) / 2, *scrollH, menu->keys.w / 4, menu->keys.h / 4 };
    // t_RGB col = {0, 0, 0, 0};
    // create_button(&win->buttonList, NULL, dest, col, col, )
    return ((void*)1);
}

int init_settings_menu(t_WIN *win, SDL_Renderer *renderer,
                       t_settings_menu *SettingsMenu)
{
    pthread_t threads[8];
    void *ret = NULL;
    int finalRet = 1;

    ft_bzero(SettingsMenu, sizeof(t_settings_menu));
    t_png *images[7] = {
        &SettingsMenu->background,
        &SettingsMenu->keys,
        &SettingsMenu->scroll,
        &SettingsMenu->scroll_grab,
        &SettingsMenu->separator,
        &SettingsMenu->slider_bar,
        &SettingsMenu->slider_grab,
    };

    const char *paths[7] = {
        "assets/png/settings/background.png",
        "assets/png/settings/keys.png",
        "assets/png/settings/horizontal-grab.png",
        "assets/png/settings/horizontal-grab.png",
        "assets/png/settings/separator.png",
        "assets/png/settings/horizontal-slider.png",
        "assets/png/settings/horizontal-grab.png"
    };

    for (int i = 0; i < 7; i++)
        images[i]->path = ft_strdup(paths[i]);

    for (int i = 0; i < 7; i++)
        pthread_create(&threads[i], NULL, process_png, images[i]);

    pthread_create(&threads[7], NULL, init_texts, win);

    for (int i = 0; i < 7; i++)
    {
        pthread_join(threads[i], &ret);

        if (!ret)
            finalRet = 0;
        else
            images[i]->texture =
                create_image(images[i], renderer);
    }
    pthread_join(threads[7], &ret);

    if (!ret)
        finalRet = 0;
    SettingsMenu->slider_grab.x = (1044 - SettingsMenu->slider_grab.w/6) / 2;
    return finalRet;
}

static void draw_texture(int x, int y, int w, int h, t_WIN *win, SDL_Texture *texture)
{
    SDL_Rect dest = { x, y, w, h };
    to_responsive(win, &dest);
    SDL_RenderCopy(win->renderPTR, texture, NULL, &dest);
}

static int draw_FOV(int yPos, int *scrollH, t_game *game, t_settings_menu *menu)
{
    t_WIN *win = game->window;
    int separatorW = menu->separator.w / 1.8;
    int separatorH = menu->separator.h / 1.8;

    yPos += 150;
    draw_texture((1044 - menu->separator.w / 1.8) / 2, yPos - *scrollH, separatorW, separatorH, win, menu->separator.texture);
    draw_texture((1044 - menu->texts[3].w) / 2, yPos + 25 - *scrollH, menu->texts[3].w, menu->texts[3].h, win, menu->texts[3].texture);
    yPos += separatorH;

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

    yPos += 40;
    draw_texture((1044 - menu->slider_bar.w/2) / 2, yPos - *scrollH, menu->slider_bar.w/2, menu->slider_bar.h/2, win, menu->slider_bar.texture);
    menu->slider_grab.y = yPos - *scrollH + ((menu->slider_bar.h/2 - menu->slider_grab.h/6) / 2);
    draw_texture(menu->slider_grab.x, menu->slider_grab.y, menu->slider_grab.w/6, menu->slider_grab.h/6, win, menu->slider_grab.texture);
    return (yPos);
}

static int draw_controls(int *scrollH, t_WIN *win, t_settings_menu *menu)
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

void    draw_settings_menu(t_game *game)
{
    SDL_Renderer *renderer = game->window->renderPTR;
    t_WIN *win = game->window;
    t_settings_menu *menu = &win->menus.settings;
    int scrollH = 0;
    int viewportX = (1920 - 1044) / 2;
    
    if (!menu->separator.texture)
        ft_printf("separator texture is NULL\n");

    game->window->menus.current = 2;

    SDL_Rect dest = { 0, 0, 1920, 1080 };
    to_responsive(win, &dest);
	SDL_RenderCopy(renderer, menu->background.texture, NULL, &dest);

    dest = (SDL_Rect){ (1920 - menu->texts[0].w) / 2, 15, menu->texts[0].w, menu->texts[0].h};
    to_responsive(win, &dest);
	SDL_RenderCopy(renderer, menu->texts[0].texture, NULL, &dest);

    /*Viewport*/
    dest = (SDL_Rect){ viewportX, 136, 1044, 842 };
    to_responsive(win, &dest);
    menu->ViewPortCoords = dest;

    // t_RGB rgb = {255, 0, 0, 255};
    // create_rectangle(renderer, dest, rgb);
    SDL_RenderSetViewport(renderer, &dest);
    int yPos = 0;
    yPos = draw_controls(&scrollH, win, menu);
    draw_FOV(yPos, &scrollH, game, menu);

    SDL_RenderSetViewport(renderer, NULL);
    /*Viewport END*/
}
//SDL_RenderSetClipRect