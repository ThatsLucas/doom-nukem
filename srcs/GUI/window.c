/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:34:18 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/20 12:05:55 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include <stdio.h>
#include "Game.h"
/*
flag == le mode d'affichage de la fenetre, fullscreen, borderless ect
https://wiki.libsdl.org/SDL2/SDL_WindowFlags
*/

// tout doit être free mise à part
int init_all_imgs(t_game *game, t_WIN *win)
{
    SDL_Color white = {255, 255, 255, 255};
    t_font font;
    font.color = white;
    font.size = 120;

    create_text(&font, win->renderPTR, game->languages->loading, DNFONT);
    SDL_Rect text_dest = {(1920 - font.w) / 2, (1080 - font.h) / 2, font.w, font.h};
    to_responsive(win, &text_dest);
    SDL_RenderCopy(win->renderPTR, font.texture, NULL, &text_dest);
    SDL_RenderPresent(win->renderPTR);
    if (!init_home_menu(game, win, win->renderPTR, &win->menus.main, 150))
        return (0);
    if (!init_notif(&win->menus.notif.Popup, win->renderPTR))
    {
        ft_dprintf(STDERR_FILENO, "ERROR NOTIF INIT\n");
        return (0);
    }
    if (!init_settings_menu(game, win->renderPTR, &win->menus.settings))
        return (0);
    if (!init_lobby_menu(game, win->renderPTR, &win->menus.lobby))
        return (0);
    if (!init_cinematics_menus(game, win->renderPTR, &win->menus.cinematic))
        return (0);
    return (1);
}

t_WIN *create_window(const char *title, int x, int y, int w, int h, Uint32 flags)
{
    t_WIN *windowDatas = malloc(sizeof(t_WIN));
    if (!windowDatas)
    {
        ft_dprintf(STDERR_FILENO, "Couldn't allocation memory for create_window. Exiting...\n");
        return NULL;
    }
    ft_bzero(windowDatas, sizeof(t_WIN));
    windowDatas->buttonList = NULL;

    windowDatas->winPTR = SDL_CreateWindow(title, x, y, w, h, flags);
    if (!windowDatas->winPTR)
    {
        ft_dprintf(STDERR_FILENO, "%s. Exiting...\n", SDL_GetError());
        return NULL;
    }

    /*
        https://wiki.libsdl.org/SDL2/SDL_RendererFlags
        SDL_RENDERER_ACCELERATED utilise l'acceleration GPU c interdit par le sujet donc je suppose SDL_RENDERER_SOFTWARE ?
    */
    windowDatas->renderPTR = SDL_CreateRenderer(windowDatas->winPTR, -1, SDL_RENDERER_SOFTWARE);
    if (!windowDatas->renderPTR || (SDL_SetRenderDrawColor(windowDatas->renderPTR, 0, 0, 0, 255) < 0))
    {
        SDL_DestroyWindow(windowDatas->winPTR);
        SDL_Quit();
        ft_dprintf(STDERR_FILENO, "%s. Exiting...\n", SDL_GetError());
        return NULL;
    }
    SDL_RenderClear(windowDatas->renderPTR);

    windowDatas->w = w;
    windowDatas->h = h;
    return windowDatas;
}
