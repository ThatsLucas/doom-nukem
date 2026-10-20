/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:50:03 by root-             #+#    #+#             */
/*   Updated: 2026/05/01 16:05:16 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/PNG.h"
#include "parser/huffman.h"

/* Alloue le tampon de décompression PNG. */
static void allocate_png_buffer(t_png *pngFile)
{
    pngFile->buf = malloc(sizeof(__uint8_t *) * pngFile->h);
    for (__uint32_t i = 0; i < pngFile->h; i++)
    {
        pngFile->buf[i] = malloc(sizeof(__uint8_t) * pngFile->w * pngFile->IHDR.bytes_per_pixel);
    }
}

/* Décode un bloc DEFLATE. */
static int decode_block(int btype, __uint8_t *out_buf, __uint32_t *out_len, size_t alloc_size, t_bitreader *bitReader)
{
    if (btype == 1)
        return (huffman_fixed(out_buf, out_len, alloc_size, bitReader));
    if (btype == 2)
        return (huffman_dynamic(out_buf, out_len, alloc_size, bitReader));
    if (btype == 0)
        return (huffman_uncompressed(out_buf, out_len, bitReader));
    ft_dprintf(STDERR_FILENO, "BTYPE 3 invalide\n");
    return (0);
}

/* Décompresse les blocs DEFLATE du PNG. */
int parse_deflate_blocs(t_png *pngFile, __uint8_t *buff, __uint64_t buffer_len)
{
    t_bitreader bitReader;
    bitReader.buffer = buff + 2;
    bitReader.byte_index = 0;
    bitReader.bit_index = 0;
    bitReader.buffer_len = buffer_len;

    size_t alloc_size = (size_t)pngFile->w * pngFile->h * pngFile->IHDR.bytes_per_pixel + pngFile->h;
    __uint8_t *out_buf = malloc(alloc_size);
    __uint32_t out_len = 0;

    allocate_png_buffer(pngFile);
    if (!pngFile->buf)
    {
        free(out_buf);
        return (0);
    }
    while (1)
    {
        __uint8_t bfinal = read_bits(&bitReader, 1);
        __uint8_t type0 = read_bits(&bitReader, 1);
        __uint8_t type1 = read_bits(&bitReader, 1);
        int btype = type0 | (type1 << 1);

        if (!decode_block(btype, out_buf, &out_len, alloc_size, &bitReader))
        {
            if (btype == 3)
                free(out_buf);
            return (0);
        }
        if (bfinal)
            break;
    }
    fill_img_buffer(pngFile, out_buf, out_len);
    free(out_buf);
    return (1);
}
