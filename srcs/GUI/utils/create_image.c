/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:52:18 by lucas             #+#    #+#             */
/*   Updated: 2026/05/05 17:05:44 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"
#include "Window.h"
#include "../../../includes/parser/PNG.h"
#include "../../../includes/parser/huffman.h"

static SDL_PixelFormatEnum decidePixelFormat(uint8_t color_type)
{
    SDL_PixelFormatEnum format;
    if (color_type == RGBA)
        format = SDL_PIXELFORMAT_RGBA32;
    else if (color_type == RGB)
        format = SDL_PIXELFORMAT_RGB24;
    else if (color_type == GRAYSCALE)
        format = SDL_PIXELFORMAT_RGB24;
    else if (color_type == GRAYSCALE_ALPHA)
        format = SDL_PIXELFORMAT_RGBA32; 
    else
        format = SDL_PIXELFORMAT_RGBA32;

    return (format);
}
SDL_Texture *create_image(t_png *pngFile, SDL_Renderer *renderer)
{
    SDL_PixelFormatEnum format = decidePixelFormat(pngFile->IHDR.color_type);
    SDL_Texture *texture = SDL_CreateTexture(renderer, format,
        SDL_TEXTUREACCESS_STREAMING, pngFile->w, pngFile->h);
	if (!texture)
    {
        ft_printf("create_image: SDL_CreateTexture failed: %s\n", SDL_GetError());
        for (uint32_t i = 0; i < pngFile->h; i++)
            free(pngFile->buf[i]);
        free(pngFile->buf);
        pngFile->buf = NULL;
        return (NULL);
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    for (uint32_t h = 0; h < pngFile->h; h++)
    {
		if (!pngFile->buf[h])
        	continue ;
        SDL_Rect line = {0, h, pngFile->w, 1};
        SDL_UpdateTexture(texture, &line, pngFile->buf[h],
            pngFile->w * pngFile->IHDR.bytes_per_pixel);
    }
    for (uint32_t i = 0; i < pngFile->h; i++) //on en a plus besoin normalements
    {
        free(pngFile->buf[i]);
    }
    free(pngFile->buf);
    pngFile->buf = NULL;
    return (texture);
}