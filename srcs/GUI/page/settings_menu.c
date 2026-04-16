/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:22:22 by lucas             #+#    #+#             */
/*   Updated: 2026/04/16 23:56:29 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

int    init_settings_menu(SDL_Renderer *renderer, t_settings_menu *SettingsMenu)
{
    pthread_t thread, thread2, thread3, thread4, thread5;
    void  *ret = NULL;
    int finalRet = 1;

    SettingsMenu->background.path = ft_strdup("assets/png/settings/background.png");
    SettingsMenu->keys.path = ft_strdup("assets/png/settings/background.png");
    SettingsMenu->scroll.path = ft_strdup("assets/png/settings/background.png");
    SettingsMenu->scroll_grab.path = ft_strdup("assets/png/settings/background.png");
    SettingsMenu->separator.path = ft_strdup("assets/png/settings/background.png");

    pthread_create(&thread, NULL, process_png, &SettingsMenu->background);
    pthread_create(&thread2, NULL, process_png, &SettingsMenu->keys);
    pthread_create(&thread3, NULL, process_png, &SettingsMenu->scroll);
    pthread_create(&thread4, NULL, process_png, &SettingsMenu->scroll_grab);
    pthread_create(&thread5, NULL, process_png, &SettingsMenu->separator);
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
    return (finalRet);
}


void    draw_settings_menu(t_game *game)
{
    SDL_Renderer *renderer = game->window->renderPTR;
    t_WIN *win = game->window;
    t_settings_menu *menu = &win->menus.settings;
    
    game->window->menus.current = 2;

    SDL_Rect bg_dest = { 0, 0, 1920, 1080 };
    to_responsive(win, &bg_dest);
	SDL_RenderCopy(renderer, menu->background.texture, NULL, &bg_dest);
}
//SDL_RenderSetClipRect