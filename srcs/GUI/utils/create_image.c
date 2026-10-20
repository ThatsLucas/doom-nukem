/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:52:18 by lucas             #+#    #+#             */
/*   Updated: 2026/09/23 12:24:08 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"
#include "Window.h"
#include "parser/PNG.h"
#include "parser/huffman.h"

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

SDL_Rect get_png_opaque_bounds(t_png *pngFile)
{
    SDL_Rect full = {0, 0, pngFile->w, pngFile->h};
    int bpp = pngFile->IHDR.bytes_per_pixel;
    int min_x = pngFile->w, min_y = pngFile->h, max_x = -1, max_y = -1;

    if (!pngFile->buf || bpp != 4)
        return (full);
    for (int y = 0; y < (int)pngFile->h; y++)
    {
        for (int x = 0; x < (int)pngFile->w; x++)
        {
            if (pngFile->buf[y][x * bpp + 3] <= 16)
                continue;
            if (x < min_x) min_x = x;
            if (x > max_x) max_x = x;
            if (y < min_y) min_y = y;
            if (y > max_y) max_y = y;
        }
    }
    if (max_x < 0)
        return (full);
    return ((SDL_Rect){min_x, min_y, max_x - min_x + 1, max_y - min_y + 1});
}

SDL_Texture *create_image(t_png *pngFile, SDL_Renderer *renderer)
{
    SDL_PixelFormatEnum format = decidePixelFormat(pngFile->IHDR.color_type);
    SDL_Texture *texture = SDL_CreateTexture(renderer, format,
        SDL_TEXTUREACCESS_STREAMING, pngFile->w, pngFile->h);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    for (uint32_t h = 0; h < pngFile->h; h++)
    {
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