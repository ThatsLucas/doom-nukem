/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:52:18 by lucas             #+#    #+#             */
/*   Updated: 2026/05/07 13:11:14 by aabouyaz         ###   ########.fr       */
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

// Dans create_image, avant la boucle SDL_UpdateTexture :
// Si c'est du grayscale, convertir chaque ligne
static uint8_t *convert_gray_to_rgb(uint8_t *row, uint32_t w, int color_type)
{
    int src_bpp;
    int dst_bpp;
    uint8_t *out;

    if (color_type == 0)
    {
        src_bpp = 1;
        dst_bpp = 3;
    }
    else if (color_type == 4)
    {
        src_bpp = 2;
        dst_bpp = 4;
    }
    else
        return (NULL);
    out = malloc(w * dst_bpp);
    for (uint32_t x = 0; x < w; x++)
    {
        out[x * dst_bpp + 0] = row[x * src_bpp];     // R = G = B = gray
        out[x * dst_bpp + 1] = row[x * src_bpp];
        out[x * dst_bpp + 2] = row[x * src_bpp];
        if (dst_bpp == 4)
            out[x * dst_bpp + 3] = row[x * src_bpp + 1]; // Alpha
    }
    return (out);
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

    int is_gray = (pngFile->IHDR.color_type == 0 || pngFile->IHDR.color_type == 4);
	int real_bpp = (pngFile->IHDR.color_type == 0) ? 3 : 
				(pngFile->IHDR.color_type == 4) ? 4 : pngFile->IHDR.bytes_per_pixel;

	for (uint32_t h = 0; h < pngFile->h; h++)
	{
		if (!pngFile->buf[h])
			continue;
		SDL_Rect line = {0, h, pngFile->w, 1};
		if (is_gray)
		{
			uint8_t *rgb = convert_gray_to_rgb(pngFile->buf[h], pngFile->w,
											pngFile->IHDR.color_type);
			SDL_UpdateTexture(texture, &line, rgb, pngFile->w * real_bpp);
			free(rgb);
		}
		else
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