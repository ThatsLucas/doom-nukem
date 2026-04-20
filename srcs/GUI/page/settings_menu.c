/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:22:22 by lucas             #+#    #+#             */
/*   Updated: 2026/04/17 21:27:50 by lucas            ###   ########.fr       */
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

    // int scrollH = 136;
    // SDL_Rect dest = { (1920 - menu->keys.w / 2) / 2, *scrollH, menu->keys.w / 4, menu->keys.h / 4 };
    // t_RGB col = {0, 0, 0, 0};
    // create_button(&win->buttonList, NULL, dest, col, col, )
    return ((void*)1);
}

int    init_settings_menu(t_WIN *win, SDL_Renderer *renderer, t_settings_menu *SettingsMenu)
{
    pthread_t thread, thread2, thread3, thread4, thread5, thread6;
    void  *ret = NULL;
    int finalRet = 1;

    SettingsMenu->background.path = ft_strdup("assets/png/settings/background.png");
    SettingsMenu->keys.path = ft_strdup("assets/png/settings/keys.png");
    SettingsMenu->scroll.path = ft_strdup("assets/png/settings/background.png");
    SettingsMenu->scroll_grab.path = ft_strdup("assets/png/settings/background.png");
    SettingsMenu->separator.path = ft_strdup("assets/png/settings/separator.png");

    pthread_create(&thread, NULL, process_png, &SettingsMenu->background);
    pthread_create(&thread2, NULL, process_png, &SettingsMenu->keys);
    pthread_create(&thread3, NULL, process_png, &SettingsMenu->scroll);
    pthread_create(&thread4, NULL, process_png, &SettingsMenu->scroll_grab);
    pthread_create(&thread5, NULL, process_png, &SettingsMenu->separator);
    pthread_create(&thread6, NULL, init_texts, win);
    pthread_join(thread, &ret);
    if (!ret)
        finalRet = 0;
    else
        SettingsMenu->background.texture = create_image(&SettingsMenu->background, renderer);

    pthread_join(thread2, &ret);
    if (!ret)
        finalRet = 0;
    else
        SettingsMenu->keys.texture = create_image(&SettingsMenu->keys, renderer);

    pthread_join(thread3, &ret);
    if (!ret)
        finalRet = 0;
    else
        SettingsMenu->scroll.texture = create_image(&SettingsMenu->scroll, renderer);

    pthread_join(thread4, &ret);
    if (!ret)
        finalRet = 0;
    else
        SettingsMenu->scroll_grab.texture = create_image(&SettingsMenu->scroll_grab, renderer);

    pthread_join(thread5, &ret);
    if (!ret)
        finalRet = 0;
    else
        SettingsMenu->separator.texture = create_image(&SettingsMenu->separator, renderer);

    pthread_join(thread6, &ret);
    if (!(int *)ret)
        finalRet = 0;
    return (finalRet);
}


static void draw_controls(int *scrollH, t_WIN *win, t_settings_menu *menu)
{
    SDL_Rect dest = { 0, 0, 1920, 1080 };
    dest = (SDL_Rect){ (1920 - menu->keys.w / 2) / 2, *scrollH, menu->keys.w / 4, menu->keys.h / 4 };
    to_responsive(win, &dest);
    SDL_RenderCopy(win->renderPTR, menu->keys.texture, NULL, &dest);
    
}

void    draw_settings_menu(t_game *game)
{

    SDL_Renderer *renderer = game->window->renderPTR;
    t_WIN *win = game->window;
    t_settings_menu *menu = &win->menus.settings;
    int scrollH = 136;
    
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
    dest = (SDL_Rect){ (1920 - 1044) / 2, 136, 1044, 842 };
    to_responsive(win, &dest);
    SDL_RenderSetViewport(renderer, &dest);



    SDL_RenderSetViewport(renderer, NULL);
    /*Viewport END*/
}
//SDL_RenderSetClipRect