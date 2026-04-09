/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root- <root-@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:50:03 by root-             #+#    #+#             */
/*   Updated: 2026/04/09 17:32:44 by root-            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser/PNG.h"
#include "../../../includes/parser/huffman.h"

static __uint8_t get_bit(__uint8_t byte, short index)
{
    __uint8_t bit = ((byte >> index) & 0x01);
    return (bit);
}

void parse_deflate_blocs(t_png *pngFile, __uint8_t *buff, __uint64_t buffer_len)
{
    t_bitreader bitReader;
    bitReader.buffer = buff;
    bitReader.byte_index = 0;
    bitReader.buffer_len = buffer_len;

    bitReader.buffer = buff + 2; //zlib header
    while (1)
    {
        t_inflate inf;
        __uint8_t state = get_bit(*(bitReader.buffer + bitReader.byte_index), 0);
        if (state == 0x0)
            inf.BFINAL = 0;
        else
            inf.BFINAL = 1;
        __uint8_t type0 = get_bit(*(bitReader.buffer + bitReader.byte_index), 1);
        __uint8_t type1 = get_bit(*(bitReader.buffer + bitReader.byte_index), 2);
        if (type0 == 0x1)
            inf.BTYPE = HUFFMAN_FIXED;
        else if (type1 == 0x1)
            inf.BTYPE = HUFFMAN_DYNAMIC;
        else
        {
            inf.BTYPE = HUFFMAN_UNCOMPRESSED;
            fill_img_buffer(pngFile, bitReader.buffer + 5); // skip 1(BFINAL) + 2(LEN) + 2(NLEN)
            break;
        }
        if (inf.BFINAL)
            break;
    }
}