/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:22:22 by lucas             #+#    #+#             */
/*   Updated: 2026/04/21 18:23:12 by lle-duc          ###   ########.fr       */
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

    menu->texts[4].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[4].size = 80;
    create_text(&menu->texts[4], renderer, "LANGUAGES", "assets/fonts/AmazDooMLeft.ttf");

    // int scrollH = 136;
    // SDL_Rect dest = { (1920 - menu->keys.w / 2) / 2, *scrollH, menu->keys.w / 4, menu->keys.h / 4 };
    // t_RGB col = {0, 0, 0, 0};
    // create_button(&win->buttonList, NULL, dest, col, col, )
    return ((void*)1);
}

int init_settings_menu(t_WIN *win, SDL_Renderer *renderer,
                       t_settings_menu *SettingsMenu)
{
    pthread_t threads[13];
    void *ret = NULL;
    int finalRet = 1;

    ft_bzero(SettingsMenu, sizeof(t_settings_menu));
    t_png *images[12] = {
        &SettingsMenu->background,
        &SettingsMenu->keys,
        &SettingsMenu->scroll,
        &SettingsMenu->scroll_grab,
        &SettingsMenu->separator,
        &SettingsMenu->slider_bar,
        &SettingsMenu->slider_grab,
        &SettingsMenu->languages[0],
        &SettingsMenu->languages[1],
        &SettingsMenu->languages[2],
        &SettingsMenu->languages[3],
        &SettingsMenu->languages[4]
    };

    const char *paths[12] = {
        "assets/png/settings/background.png",
        "assets/png/settings/keys.png",
        "assets/png/settings/scroll.png",
        "assets/png/settings/scroll_grab.png",
        "assets/png/settings/separator.png",
        "assets/png/settings/horizontal-slider.png",
        "assets/png/settings/horizontal-grab.png",
        "assets/png/settings/languages/language_england.png",
        "assets/png/settings/languages/language_france.png",
        "assets/png/settings/languages/language_maroco.png",
        "assets/png/settings/languages/language_serbia.png",
        "assets/png/settings/languages/language_selected.png",
    };

    for (int i = 0; i < 12; i++)
    {
        printf("i = %d\n", i);
        images[i]->path = ft_strdup(paths[i]);
    }

    for (int i = 0; i < 12; i++)
        pthread_create(&threads[i], NULL, process_png, images[i]);

    pthread_create(&threads[12], NULL, init_texts, win);

    for (int i = 0; i < 12; i++)
    {
        pthread_join(threads[i], &ret);

        if (!ret)
            finalRet = 0;
        else
            images[i]->texture =
                create_image(images[i], renderer);
    }
    pthread_join(threads[12], &ret);

    if (!ret)
        finalRet = 0;
    SettingsMenu->slider_grab.x = (1044 - SettingsMenu->slider_grab.w/6) / 2;
    SettingsMenu->scroll_grab.y = 40;
    return finalRet;
}

void    draw_settings_menu(t_game *game)
{
    SDL_Renderer *renderer = game->window->renderPTR;
    t_WIN *win = game->window;
    t_settings_menu *menu = &win->menus.settings;
    int viewportX = (1920 - 1044) / 2;

    game->window->menus.current = 2;

    draw_texture(0, 0, 1920, 1080, win, menu->background.texture);
    draw_texture((1920 - menu->texts[0].w) / 2, 15, menu->texts[0].w, menu->texts[0].h, win, menu->texts[0].texture);
    draw_scroll_bar(game, menu);

    /*Viewport*/
    SDL_Rect dest = { viewportX, 136, 1044, 842 };
    to_responsive(win, &dest);
    menu->ViewPortCoords = dest;

    // t_RGB rgb = {255, 0, 0, 255};
    // create_rectangle(renderer, dest, rgb);
    SDL_RenderSetViewport(renderer, &dest);
    int yPos = 0;
    yPos = draw_controls(&menu->scrollH, win, menu);
    yPos = draw_FOV(yPos, &menu->scrollH, game, menu);
    yPos = draw_languages(yPos, &menu->scrollH, game, menu);

    SDL_RenderSetViewport(renderer, NULL);
    /*Viewport END*/
}
//SDL_RenderSetClipRect