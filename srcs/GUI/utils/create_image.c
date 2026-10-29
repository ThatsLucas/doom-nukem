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

/* Détermine le format de couleur des pixels. */
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

/* Calcule le rectangle des pixels non transparents du PNG. */
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

/* Convertit une ligne en niveaux de gris vers le format RGB/RGBA de la texture. */
static void expand_gray_row(t_png *pngFile, uint8_t *src, uint8_t *dst, int dst_bpp)
{
    int bpp = pngFile->IHDR.bytes_per_pixel;

    for (uint32_t x = 0; x < pngFile->w; x++)
    {
        dst[x * dst_bpp] = src[x * bpp];
        dst[x * dst_bpp + 1] = src[x * bpp];
        dst[x * dst_bpp + 2] = src[x * bpp];
        if (dst_bpp == 4)
            dst[x * dst_bpp + 3] = src[x * bpp + 1];
    }
}

/* Crée une texture SDL à partir d’un PNG décodé. */
SDL_Texture *create_image(t_png *pngFile, SDL_Renderer *renderer)
{
    SDL_PixelFormatEnum format = decidePixelFormat(pngFile->IHDR.color_type);
    SDL_Texture *texture = SDL_CreateTexture(renderer, format,
        SDL_TEXTUREACCESS_STREAMING, pngFile->w, pngFile->h);
    int is_gray = (pngFile->IHDR.color_type == GRAYSCALE
        || pngFile->IHDR.color_type == GRAYSCALE_ALPHA);
    int dst_bpp = (pngFile->IHDR.color_type == GRAYSCALE) ? 3 : 4;
    uint8_t *gray_row = NULL;

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    if (is_gray)
        gray_row = malloc(pngFile->w * dst_bpp);
    for (uint32_t h = 0; h < pngFile->h; h++)
    {
        SDL_Rect line = {0, h, pngFile->w, 1};
        if (is_gray && gray_row)
        {
            expand_gray_row(pngFile, pngFile->buf[h], gray_row, dst_bpp);
            SDL_UpdateTexture(texture, &line, gray_row, pngFile->w * dst_bpp);
        }
        else if (!is_gray)
            SDL_UpdateTexture(texture, &line, pngFile->buf[h],
                pngFile->w * pngFile->IHDR.bytes_per_pixel);
    }
    free(gray_row);
    for (uint32_t i = 0; i < pngFile->h; i++) //on en a plus besoin normalements
    {
        free(pngFile->buf[i]);
    }
    free(pngFile->buf);
    pngFile->buf = NULL;
    return (texture);
}