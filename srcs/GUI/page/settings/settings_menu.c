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

static void change_menu_to_main_menu(t_game *game)
{
    if (game->is_paused == 1)
    {
        game->window->menus.current = 0;
        return;
    }
    game->window->menus.current = 1;
}

static void *init_texts(void *gameStruct)
{
    t_game *game = (t_game *)gameStruct;
    t_WIN *win = game->window;
    t_languages *lang = game->languages;
    SDL_Renderer *renderer = win->renderPTR;
    t_settings_menu *menu = &win->menus.settings;
    menu->texts[0].size = 80;
    menu->texts[0].color = (SDL_Color){255, 255, 255, 255};
    create_text(&menu->texts[0], renderer, lang->settings, DNFONT);
    menu->texts[1].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[1].size = 50;
    create_text(&menu->texts[1], renderer, lang->move_forward, DNFONT);

    menu->texts[2].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[2].size = 50;
    create_text(&menu->texts[2], renderer, lang->move_backward, DNFONT);

    menu->texts[3].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[3].size = 80;
    create_text(&menu->texts[3], renderer, lang->fov, DNFONT);

    menu->texts[4].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[4].size = 80;
    create_text(&menu->texts[4], renderer, lang->languages, DNFONT);

    menu->texts[5].color = (SDL_Color){221, 21, 0, 255};
    menu->texts[5].size = 60;
    menu->texts[5].textHOffset = -10;
    create_text(&menu->texts[5], renderer, lang->main_menu, DNFONT);

    menu->texts[6].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[6].size = 60;
    menu->texts[6].textHOffset = -10;
    create_text(&menu->texts[6], renderer, lang->main_menu, DNFONTOUTLINED);

    menu->texts[7].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[7].size = 50;
    create_text(&menu->texts[7], renderer, lang->move_left, DNFONT);

    menu->texts[8].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[8].size = 50;
    create_text(&menu->texts[8], renderer, lang->move_right, DNFONT);

    /*CONTROLS*/
    menu->texts[9].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[9].size = 80;
    create_text(&menu->texts[9], renderer, (char *)&game->settings.move_forward, DNFONT);

    menu->texts[10].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[10].size = 80;
    create_text(&menu->texts[10], renderer, (char *)&game->settings.move_backward, DNFONT);

    menu->texts[11].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[11].size = 80;
    create_text(&menu->texts[11], renderer, (char *)&game->settings.move_left, DNFONT);

    menu->texts[12].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[12].size = 80;
    create_text(&menu->texts[12], renderer, (char *)&game->settings.move_right, DNFONT);

    menu->texts[13].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[13].size = 80;
    create_text(&menu->texts[13], renderer, lang->pick_a_key, DNFONT);

    menu->texts[14].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[14].size = 80;
    create_text(&menu->texts[14], renderer, lang->resolution, DNFONT);

    menu->texts[15].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[15].size = 70;
    create_text(&menu->texts[15], renderer, "1280 x 720", DNFONT);

    menu->texts[16].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[16].size = 70;
    create_text(&menu->texts[16], renderer, "1920 x 1080", DNFONT);

    menu->texts[17].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[17].size = 70;
    create_text(&menu->texts[17], renderer, "2560 x 1440", DNFONT);

    menu->texts[18].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[18].size = 70;
    create_text(&menu->texts[18], renderer, lang->display_mode, DNFONT);

    menu->texts[19].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[19].size = 70;
    create_text(&menu->texts[19], renderer, lang->fullscreen, DNFONT);

    menu->texts[20].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[20].size = 70;
    create_text(&menu->texts[20], renderer, lang->borderless, DNFONT);

    menu->texts[21].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[21].size = 70;
    create_text(&menu->texts[21], renderer, lang->windowed, DNFONT);

    menu->texts[22].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[22].size = 70;
    create_text(&menu->texts[22], renderer, lang->mouse_sensi, DNFONT);

    t_RGB color = {255, 255, 255, 0};
    SDL_Rect coords = {20, 20, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &change_menu_to_main_menu, coords, color, color, &menu->texts[6], &menu->texts[5], 2);

    /*LANGUAGES*/
    // create_button(&win->buttonList, &change_menu_to_main_menu, (SDL_Rect){1000, 900, 100, 100}, color, color, NULL, NULL, 2);
    // create_button(&win->buttonList, &change_menu_to_main_menu, coords, color, color, NULL, NULL, 2);
    // create_button(&win->buttonList, &change_menu_to_main_menu, coords, color, color, NULL, NULL, 2);
    // create_button(&win->buttonList, &change_menu_to_main_menu, coords, color, color, NULL, NULL, 2);

    return ((void *)1);
}

int init_settings_menu(t_game *game, SDL_Renderer *renderer,
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
        &SettingsMenu->languages[4]};

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
        images[i]->path = ft_strdup(paths[i]);

    for (int i = 0; i < 12; i++)
        pthread_create(&threads[i], NULL, process_png, images[i]);

    pthread_create(&threads[12], NULL, init_texts, game);

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
    SettingsMenu->slider_grab.x = (1044 - SettingsMenu->slider_grab.w / 6) / 2;
    SettingsMenu->scroll_grab.y = 40;

    SettingsMenu->MouseSensiCoords = (SDL_Rect){(1044 - SettingsMenu->slider_grab.w / 6) / 2, 40, SettingsMenu->slider_grab.w / 6, SettingsMenu->slider_grab.h / 6};
    return finalRet;
}

void draw_settings_menu(t_game *game)
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
    SDL_Rect dest = {viewportX, 136, 1044, 842};
    to_responsive(win, &dest);
    menu->ViewPortCoords = dest;

    // t_RGB rgb = {255, 0, 0, 255};
    // create_rectangle(renderer, dest, rgb);
    SDL_RenderSetViewport(renderer, &dest);
    int yPos = 0;
    yPos = draw_controls(&menu->scrollH, win, menu);
    yPos = draw_FOV(yPos, &menu->scrollH, game, menu);
    yPos = draw_mouse_sensibility(yPos, &menu->scrollH, game, menu);
    yPos = draw_languages(yPos, &menu->scrollH, game, menu);
    yPos = draw_resolution(yPos, &menu->scrollH, game, menu);
    yPos = draw_display_mode(yPos, &menu->scrollH, game, menu);

    SDL_RenderSetViewport(renderer, NULL);
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
// SDL_RenderSetClipRect