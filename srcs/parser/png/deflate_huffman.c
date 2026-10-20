/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deflate_huffman.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:24:26 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:24:26 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/PNG.h"
#include "parser/huffman.h"

/* Décode les symboles d’un bloc compressé jusqu’à la fin du bloc. */
void read_compressed_datas(__uint8_t *buf, __uint32_t *buf_len, size_t max_len, t_bitreader *bitReader, int *lit_symbol, int *lit_len, int *dist_symbol, int *dist_len)
{
    while (1)
    {
        int sym = read_symbol(bitReader, lit_symbol, lit_len, 15);
        if (sym >= 0 && sym <= 255)
        {
            buf[*buf_len] = (__uint8_t)sym;
            *buf_len += 1;
        }
        else if (sym == 256)
            break;
        else
            lz77(buf, buf_len, max_len, bitReader, sym, dist_symbol, dist_len);
    }
}

/* Alloue et initialise les tables de décodage Huffman. */
static void alloc_huffman_tables(int **lit_symbol, int **lit_len, int **dist_symbol, int **dist_len)
{
    *lit_symbol  = malloc(32768 * sizeof(int));
    *lit_len     = malloc(32768 * sizeof(int));
    *dist_symbol = malloc(32768 * sizeof(int));
    *dist_len    = malloc(32768 * sizeof(int));
    ft_bzero(*lit_symbol,  32768 * sizeof(int));
    ft_bzero(*lit_len,     32768 * sizeof(int));
    ft_bzero(*dist_symbol, 32768 * sizeof(int));
    ft_bzero(*dist_len,    32768 * sizeof(int));
}

/* Libère les tables de décodage Huffman. */
static void free_huffman_tables(int *lit_symbol, int *lit_len, int *dist_symbol, int *dist_len)
{
    free(lit_symbol);
    free(lit_len);
    free(dist_symbol);
    free(dist_len);
}

/* Décode un bloc DEFLATE à codes Huffman fixes. */
int huffman_fixed(__uint8_t *buf, __uint32_t *buf_len, size_t max_len, t_bitreader *bitReader)
{
    int *lit_symbol, *lit_len, *dist_symbol, *dist_len;
    int lengths[288];

    alloc_huffman_tables(&lit_symbol, &lit_len, &dist_symbol, &dist_len);
    for (int i = 0; i <= 143; i++)   lengths[i] = 8;
    for (int i = 144; i <= 255; i++) lengths[i] = 9;
    for (int i = 256; i <= 279; i++) lengths[i] = 7;
    for (int i = 280; i <= 287; i++) lengths[i] = 8;
    build_code_table(lengths, 288, lit_symbol, lit_len);

    for (int i = 0; i < 30; i++)
    {
        dist_symbol[i] = i;
        dist_len[i] = 5;
    }

    read_compressed_datas(buf, buf_len, max_len, bitReader, lit_symbol, lit_len, dist_symbol, dist_len);
    free_huffman_tables(lit_symbol, lit_len, dist_symbol, dist_len);
    return (1);
}

/* Décode un bloc DEFLATE à codes Huffman dynamiques. */
int huffman_dynamic(__uint8_t *buf, __uint32_t *buf_len, size_t max_len, t_bitreader *bitReader)
{
    __uint32_t HLIT = read_bits(bitReader, 5) + 257;
    __uint32_t HDIST = read_bits(bitReader, 5) + 1;
    __uint32_t HCLEN = read_bits(bitReader, 4) + 4;
    int *lit_symbol, *lit_len, *dist_symbol, *dist_len;

    alloc_huffman_tables(&lit_symbol, &lit_len, &dist_symbol, &dist_len);
    build_meta_tree(HLIT, HDIST, HCLEN, bitReader, lit_symbol, lit_len, dist_symbol, dist_len);
    read_compressed_datas(buf, buf_len, max_len, bitReader, lit_symbol, lit_len, dist_symbol, dist_len);
    free_huffman_tables(lit_symbol, lit_len, dist_symbol, dist_len);
    return (1);
}

/* Copie un bloc DEFLATE non compressé. */
int huffman_uncompressed(__uint8_t *buf, __uint32_t *buf_len, t_bitreader *bitReader)
{
    __uint32_t LEN;
    __uint32_t NLEN;

    bitReader->byte_index += 1;
    LEN =  bitReader->buffer[bitReader->byte_index] | (bitReader->buffer[bitReader->byte_index + 1] << 8);
    NLEN =  bitReader->buffer[bitReader->byte_index + 2] | (bitReader->buffer[bitReader->byte_index + 3] << 8);
    bitReader->byte_index += 4;
    if ((LEN ^ NLEN) != 0xFFFF)
    {
        ft_dprintf(STDERR_FILENO, "Bloc corrompu\n");
        return (0);
    }
    ft_memcpy(buf + *buf_len, bitReader->buffer + bitReader->byte_index, LEN);
    *buf_len += LEN;
    bitReader->byte_index += LEN;
    return (1);
}
