/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:22:22 by lucas             #+#    #+#             */
/*   Updated: 2026/04/15 23:02:12 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

void    init_settings_menu(SDL_Renderer *renderer, t_settings_menu *SettingsMenu)
{
    pthread_t thread, thread2, thread3;
    void  *ret = NULL;
    int finalRet = 1;

    MainMenu->background.path = ft_strdup("assets/png/main_menu/background.png");
    MainMenu->logo.path = ft_strdup("assets/png/main_menu/logo.png");
    MainMenu->button.path = ft_strdup("assets/png/main_menu/button.png");
    pthread_create(&thread, NULL, process_png, &MainMenu->background);
    pthread_create(&thread2, NULL, process_png, &MainMenu->logo);
    pthread_create(&thread3, NULL, process_png, &MainMenu->button);
    
    pthread_join(thread, &ret);
    if (!ret)
        finalRet = 0;
    else
        MainMenu->background.texture = create_image(&MainMenu->background, renderer);

    pthread_join(thread2, &ret);
    if (!ret)
        finalRet = 0;
    else
        MainMenu->logo.texture = create_image(&MainMenu->logo, renderer);

    pthread_join(thread3, &ret);
    if (!ret)
        finalRet = 0;
    else
        MainMenu->button.texture = create_image(&MainMenu->button, renderer);
    return (finalRet);
}

//SDL_RenderSetClipRect