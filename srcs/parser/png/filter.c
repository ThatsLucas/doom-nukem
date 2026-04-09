/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root- <root-@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:34:27 by root-             #+#    #+#             */
/*   Updated: 2026/04/09 17:25:53 by root-            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser/PNG.h"
#include "../../../includes/parser/filter.h"
#include "../../../includes/parser/huffman.h"

static __uint8_t abs_value(int val)
{
    if (val < 0)
        return (-val);
    return (val);
}

static __uint8_t paeth(t_filterType fType)
{
    int estimate = fType.left + fType.top - fType.topleft;
    __uint8_t top_diff = abs_value(estimate - (int)fType.top);
    __uint8_t left_diff = abs_value(estimate - (int)fType.left);
    __uint8_t topleft_diff = abs_value(estimate - (int)fType.topleft);

    if (left_diff <= top_diff && left_diff  <= topleft_diff)
        return (fType.left);
    else if (top_diff <= topleft_diff)
        return (fType.top);
    return (fType.topleft);
}

static __uint8_t apply_filter(__uint8_t filter, __uint8_t byte, t_filterType fType)
{
    if (filter == FILTER_NONE)
        return (byte);
    if (filter == FILTER_SUB)
        return (byte + fType.left);
    if (filter == FILTER_UP)
        return (byte + fType.top);
    if (filter == FILTER_AVERAGE)
        return (byte + ((fType.left + fType.top) / 2));
    return (paeth(fType));    
}

static t_filterType find_filter_direction(int i, int j, int bytes_per_pixel, __uint8_t **pngBuff)
{
    t_filterType fType;

    if (i == 0)
        fType.top = 0;
    else
        fType.top = pngBuff[i-1][j];
    
    if (j == 0)
        fType.left = 0;
    else
        fType.left = pngBuff[i][j-bytes_per_pixel];

    if (i == 0 || j == 0)
        fType.topleft = 0;
    else
        fType.topleft = pngBuff[i-1][j-bytes_per_pixel];
    return (fType);
}

void fill_img_buffer(t_png *pngFile, __uint8_t *buff)
{
    __uint32_t w = pngFile->w;
    __uint32_t h = pngFile->h;
    int bytesPerPixel = pngFile->IHDR.bytes_per_pixel;
    pngFile->buf = malloc(sizeof(__uint8_t *) * h);
    for (__uint32_t i = 0; i < h; i++)
    {
        pngFile->buf[i] = malloc(sizeof(__uint8_t) * w * bytesPerPixel);
    }
    ft_printf("bytesPerPixel = %d\n", pngFile->IHDR.bytes_per_pixel);
    ft_printf("w = %d, h = %d\n", pngFile->w, pngFile->h);
    ft_printf("premier octet du buffer = %d\n", buff[0]);
    __uint32_t filter = 0;
    __uint32_t cursor = 1;
    for (__uint32_t i = 0; i < h; i++)
    {
        
        for (__uint32_t j = 0; j < w * bytesPerPixel; j++)
        {
            pngFile->buf[i][j] = apply_filter(buff[filter], buff[cursor], find_filter_direction(i, j, bytesPerPixel, pngFile->buf));
            cursor++;
        }
        filter +=  w * bytesPerPixel + 1;
        cursor = filter + 1;
    }
}