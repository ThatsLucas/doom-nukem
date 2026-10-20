/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:09:07 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:09:07 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

/* Retourne au menu principal. */
static void change_menu_to_main_menu(t_game *game)
{
    if (game->is_paused == 1)
    {
        game->window->menus.current = 0;
        return;
    }
    game->window->menus.current = 1;
}

/* Initialise les textes du menu des paramètres. */
static void *init_texts(void *gameStruct)
{
    t_game *game = (t_game *)gameStruct;
    t_WIN *win = game->window;
    t_settings_menu *menu = &win->menus.settings;

    init_settings_texts(game);

    t_RGB color = {255, 255, 255, 0};
    SDL_Rect coords = {20, 20, win->menus.main.button.w / 5, win->menus.main.button.h / 5};
    create_button(&win->buttonList, &change_menu_to_main_menu, coords, color, color, &menu->texts[6], &menu->texts[5], 2);

    return ((void *)1);
}

/* Définit les images du menu des paramètres. */
static void set_settings_images(t_settings_menu *SettingsMenu, t_png **images)
{
    t_png *list[12] = {
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
    {
        images[i] = list[i];
        images[i]->path = ft_strdup(paths[i]);
    }
}

/* Initialise le menu des paramètres. */
int init_settings_menu(t_game *game, SDL_Renderer *renderer,
                       t_settings_menu *SettingsMenu)
{
    pthread_t threads[13];
    void *ret = NULL;
    int finalRet;

    ft_bzero(SettingsMenu, sizeof(t_settings_menu));
    t_png *images[12];

    set_settings_images(SettingsMenu, images);

    for (int i = 0; i < 12; i++)
        pthread_create(&threads[i], NULL, process_png, images[i]);

    pthread_create(&threads[12], NULL, init_texts, game);

    finalRet = join_png_threads(threads, images, 12, renderer);
    pthread_join(threads[12], &ret);

    if (!ret)
        finalRet = 0;
    SettingsMenu->slider_grab.x = (1044 - SettingsMenu->slider_grab.w / 6) / 2;
    SettingsMenu->scroll_grab.y = 40;

    SettingsMenu->MouseSensiCoords = (SDL_Rect){(1044 - SettingsMenu->slider_grab.w / 6) / 2, 40, SettingsMenu->slider_grab.w / 6, SettingsMenu->slider_grab.h / 6};
    return finalRet;
}
