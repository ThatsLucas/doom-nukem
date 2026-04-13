/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:34:18 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/11 23:49:25 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include <stdio.h>

/* 
flag == le mode d'affichage de la fenetre, fullscreen, borderless ect
https://wiki.libsdl.org/SDL2/SDL_WindowFlags 
*/
t_WIN* create_window(const char *title, int x, int y, int w, int h, Uint32 flags)
{
    t_WIN* windowDatas = malloc(sizeof(t_WIN));
    if (!windowDatas)
    {
        fprintf(stderr, "Couldn't allocation memory for create_window. Exiting...\n");
        return NULL;
    }
    windowDatas->buttonList = NULL;
    
    windowDatas->winPTR = SDL_CreateWindow(title, x, y, w, h, flags);
    if (!windowDatas->winPTR)
    {
        fprintf(stderr, "%s. Exiting...\n", SDL_GetError());
        return NULL;
    }

    /*
        https://wiki.libsdl.org/SDL2/SDL_RendererFlags
        SDL_RENDERER_ACCELERATED utilise l'acceleration GPU c interdit par le sujet donc je suppose SDL_RENDERER_SOFTWARE ?
    */
    windowDatas->renderPTR = SDL_CreateRenderer( windowDatas->winPTR, -1, SDL_RENDERER_SOFTWARE );
    if (!windowDatas->renderPTR || (SDL_SetRenderDrawColor( windowDatas->renderPTR, 255, 0, 0, 255 ) < 0))
    {
        SDL_DestroyWindow(windowDatas->winPTR);
        SDL_Quit();
        fprintf(stderr, "%s. Exiting...\n", SDL_GetError());
        return NULL;
    }
    SDL_RenderClear(windowDatas->renderPTR);

    windowDatas->w = w;
    windowDatas->h = h;
    return windowDatas;
}
