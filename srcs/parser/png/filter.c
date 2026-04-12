/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:34:27 by root-             #+#    #+#             */
/*   Updated: 2026/04/12 10:58:33 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser/PNG.h"
#include "../../../includes/parser/filter.h"
#include "../../../includes/parser/huffman.h"

static int abs_value(int val)
{
    if (val < 0)
        return (-val);
    return (val);
}

static int paeth(t_filterType fType)
{
    int estimate = fType.left + fType.top - fType.topleft;
    int top_diff = abs_value(estimate - (int)fType.top);
    int left_diff = abs_value(estimate - (int)fType.left);
    int topleft_diff = abs_value(estimate - (int)fType.topleft);

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
    return (byte + paeth(fType));    
}

static t_filterType find_filter_direction(int i, int j, int bytes_per_pixel, __uint8_t **pngBuff)
{
    t_filterType fType;

    if (i == 0)
        fType.top = 0;
    else
        fType.top = pngBuff[i-1][j];
    
    if (j < bytes_per_pixel)
        fType.left = 0;
    else
        fType.left = pngBuff[i][j - bytes_per_pixel];

    if (i == 0 || j < bytes_per_pixel)
        fType.topleft = 0;
    else
        fType.topleft = pngBuff[i-1][j - bytes_per_pixel];
    return (fType);
}

void fill_img_buffer(t_png *pngFile, __uint8_t *buff, __uint32_t len)
{
    __uint32_t i = 0;
    __uint32_t j = 0;
    __uint32_t w = pngFile->w;
    __uint32_t h = pngFile->h;
    int bytesPerPixel = pngFile->IHDR.bytes_per_pixel;

    __uint32_t filter = 0;
    __uint32_t cursor = 1;
    while (i < h && len > 0)
    {
        
        while (j < w * bytesPerPixel && len > 0)
        {
            pngFile->buf[i][j] = apply_filter(buff[filter], buff[cursor], find_filter_direction(i, j, bytesPerPixel, pngFile->buf));
            cursor++;
            j++;
            len--;
        }
        j = 0;
        filter +=  w * bytesPerPixel + 1;
        cursor = filter + 1;
        i++;
        len--;
    }
}