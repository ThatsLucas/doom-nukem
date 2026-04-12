/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:10:18 by lucas             #+#    #+#             */
/*   Updated: 2026/04/12 17:34:49 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI.h"
#include <SDL_ttf.h>

void create_text(t_font *textData, SDL_Renderer  *renderer, char *text, char *fontPath)
{
    textData->font = TTF_OpenFont(fontPath, textData->size);
    if (!textData->font)
        ft_printf("Error while opening font : %s\n", TTF_GetError());
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(textData->font, text, textData->color); 
    textData->texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    TTF_SizeText(textData->font, text, &textData->w, &textData->h);
}