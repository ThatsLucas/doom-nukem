/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:10:18 by lucas             #+#    #+#             */
/*   Updated: 2026/05/05 12:42:42 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"
#include <SDL_ttf.h>

/* Crée la texture d’un texte sur une ligne. */
void create_text(t_font *textData, SDL_Renderer  *renderer, char *text, char *fontPath)
{
    textData->font = TTF_OpenFont(fontPath, textData->size);
    if (!textData->font)
        ft_dprintf(STDERR_FILENO, "Error while opening font : %s\n", TTF_GetError());
    SDL_Surface* surfaceMessage = TTF_RenderUTF8_Solid(textData->font, text, textData->color); 
    if (!surfaceMessage)
        return;
    textData->texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    TTF_SizeText(textData->font, text, &textData->w, &textData->h);
    TTF_CloseFont(textData->font);
}

/* Crée la texture d’un texte sur plusieurs lignes. */
void create_text_multiple_lines(t_font *textData, SDL_Renderer  *renderer, char *text, char *fontPath, uint32_t maxW)
{
    textData->font = TTF_OpenFont(fontPath, textData->size);
    if (!textData->font)
        ft_dprintf(STDERR_FILENO, "Error while opening font : %s\n", TTF_GetError());
    SDL_Surface* surfaceMessage = TTF_RenderUTF8_Solid_Wrapped(textData->font, text, textData->color, maxW);
    if (!surfaceMessage)
        return;
    textData->texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    textData->w = surfaceMessage->w;
    textData->h = surfaceMessage->h;
    SDL_FreeSurface(surfaceMessage);
    TTF_CloseFont(textData->font);
}