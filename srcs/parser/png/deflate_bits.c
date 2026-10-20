/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deflate_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:24:26 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:24:26 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/PNG.h"
#include "parser/huffman.h"

static __uint8_t get_bit(__uint8_t byte, short index)
{
    __uint8_t bit = ((byte >> index) & 0x01);
    return (bit);
}

__uint32_t read_bits(t_bitreader *bitReader, int bitsToRead)
{
    __uint32_t ret = 0;
    for (int i = 0; i < bitsToRead; i++)
    {
        ret = ret | (get_bit(bitReader->buffer[bitReader->byte_index], bitReader->bit_index) << i); 
        bitReader->bit_index++;
        if (bitReader->bit_index == 8)
        {
            bitReader->bit_index = 0;
            bitReader->byte_index++;
        }
    }
    return (ret);
}

int read_symbol(t_bitreader *bitReader, int *table_symbol, int *table_len, int maxbits)
{
    int code = 0;
    for (int len = 1; len <= maxbits; len++)
    {
        code = (code << 1) | read_bits(bitReader, 1);
        if (table_len[code] == len)
            return table_symbol[code];
    }
    return -1;
}
