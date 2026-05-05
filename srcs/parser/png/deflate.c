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

#include "../../../includes/parser/PNG.h"
#include "../../../includes/parser/huffman.h"

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

static void allocate_png_buffer(t_png *pngFile)
{
    pngFile->buf = malloc(sizeof(__uint8_t *) * pngFile->h);
    for (__uint32_t i = 0; i < pngFile->h; i++)
    {
        pngFile->buf[i] = malloc(sizeof(__uint8_t) * pngFile->w * pngFile->IHDR.bytes_per_pixel);
    }
}

static void push_value_n_times(int *lengths, __uint32_t *i, __uint32_t HLIT, __uint32_t HDIST, int n, int bit, t_bitreader *bitReader, int val)
{
    __uint32_t repeat = read_bits(bitReader, bit) + n;
    while(repeat && *i < HLIT + HDIST)
    {
        lengths[*i] = val;
        repeat--;
        *i = *i + 1;
    }
    *i -= 1;
}

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

static void build_litteral_tree(int *lengths, __uint32_t HLIT, __uint32_t HDIST, int *lit_symbol, int *lit_len, int *dist_symbol, int *dist_len)
{
    int frequecy[16] = {0};
    int first_code[16] = {0};

    for (__uint32_t i = 0; i < HLIT; i++)
        frequecy[lengths[i]]++;
    for (__uint32_t i = 1; i <= 14; i++)
        first_code[i+1] = (first_code[i] + frequecy[i]) << 1;
    for (__uint32_t i = 0; i < HLIT; i++)
    {
        if (lengths[i] > 0)
        {
            lit_symbol[first_code[lengths[i]]] = i;
            lit_len[first_code[lengths[i]]]    = lengths[i];
            first_code[lengths[i]]++;
        }
    }

    ft_memset(frequecy, 0, sizeof(frequecy));
    ft_memset(first_code, 0, sizeof(first_code));

    for (__uint32_t i = 0; i < HDIST; i++)
        frequecy[lengths[HLIT + i]]++;
    for (__uint32_t i = 1; i <= 14; i++)
        first_code[i+1] = (first_code[i] + frequecy[i]) << 1;
    for (__uint32_t i = 0; i < HDIST; i++)
    {
        if (lengths[HLIT + i] > 0)
        {
            dist_symbol[first_code[lengths[HLIT + i]]] = i;
            dist_len[first_code[lengths[HLIT + i]]]    = lengths[HLIT + i];
            first_code[lengths[HLIT + i]]++;
        }
    }
}

static void build_meta_tree(__uint32_t HLIT, __uint32_t HDIST, __uint32_t HCLEN, t_bitreader *bitReader, int *lit_symbol, int *lit_len, int *dist_symbol, int *dist_len)
{
    int order[19] = {16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15};
    int code_len[19] = {0};
    for (__uint32_t i = 0; i < HCLEN; i++)
        code_len[order[i]] = read_bits(bitReader, 3);
    int frequecy[19] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 19; i++)
        frequecy[code_len[i]] += 1;
    int first_code[8];
    first_code[0] = 0;
    first_code[1] = 0;
    for (int i = 1; i < 7; i++)
        first_code[i+1] =  (first_code[i] + frequecy[i]) << 1;

    int table_symbol[128] = {0};
    int table_len[128] = {0};

    for (int i = 0; i < 19; i++)
    {
        if (code_len[i] > 0)
        {
            table_symbol[first_code[code_len[i]]] = i;
            table_len[first_code[code_len[i]]] = code_len[i];
            first_code[code_len[i]] += 1;
        }
    }
    int *lengths = malloc((HLIT + HDIST)  * sizeof(int));
    ft_bzero(lengths,  (HLIT + HDIST) * sizeof(int));

    for (__uint32_t i = 0; i < HLIT + HDIST; i++)
    {
        int sym = read_symbol(bitReader, table_symbol, table_len, 7);
        if (sym >= 0 && sym <= 15)
            lengths[i] = sym;
        else if (sym == 16)
        {
            push_value_n_times(lengths, &i, HLIT, HDIST, 3, 2, bitReader, lengths[i - 1]);
        }
        else if (sym == 17)
        {
            push_value_n_times(lengths, &i, HLIT, HDIST, 3, 3, bitReader, 0);
        }
        else if (sym == 18)
        {
            push_value_n_times(lengths, &i, HLIT, HDIST, 11, 7, bitReader, 0);
        }
    }
    build_litteral_tree(lengths, HLIT, HDIST, lit_symbol, lit_len, dist_symbol, dist_len);
    free(lengths);
}

int huffman_fixed(__uint8_t *buf, __uint32_t *buf_len, size_t max_len, t_bitreader *bitReader)
{
    int *lit_symbol = malloc(32768 * sizeof(int));
    int *lit_len    = malloc(32768 * sizeof(int));
    int *dist_symbol = malloc(32768 * sizeof(int));
    int *dist_len   = malloc(32768 * sizeof(int));

    ft_bzero(lit_symbol, 32768 * sizeof(int));
    ft_bzero(lit_len, 32768 * sizeof(int));
    ft_bzero(dist_symbol, 32768 * sizeof(int));
    ft_bzero(dist_len, 32768 * sizeof(int));

    int lengths[288];
    for (int i = 0; i <= 143; i++)   lengths[i] = 8;
    for (int i = 144; i <= 255; i++) lengths[i] = 9;
    for (int i = 256; i <= 279; i++) lengths[i] = 7;
    for (int i = 280; i <= 287; i++) lengths[i] = 8;

    int frequecy[16] = {0};
    int first_code[16] = {0};
    for (int i = 0; i < 288; i++) frequecy[lengths[i]]++;
    for (int i = 1; i <= 14; i++) first_code[i+1] = (first_code[i] + frequecy[i]) << 1;
    for (int i = 0; i < 288; i++)
    {
        if (lengths[i] > 0)
        {
            lit_symbol[first_code[lengths[i]]] = i;
            lit_len[first_code[lengths[i]]] = lengths[i];
            first_code[lengths[i]]++;
        }
    }

    for (int i = 0; i < 30; i++)
    {
        dist_symbol[i] = i;
        dist_len[i] = 5;
    }

    read_compressed_datas(buf, buf_len, max_len, bitReader, lit_symbol, lit_len, dist_symbol, dist_len);

    free(lit_symbol);
    free(lit_len);
    free(dist_symbol);
    free(dist_len);
    return (1);
}

int huffman_dynamic(__uint8_t *buf, __uint32_t *buf_len, size_t max_len, t_bitreader *bitReader)
{
    __uint32_t HLIT = read_bits(bitReader, 5) + 257;
    __uint32_t HDIST = read_bits(bitReader, 5) + 1;
    __uint32_t HCLEN = read_bits(bitReader, 4) + 4;
    int *lit_symbol  = malloc(32768 * sizeof(int));
    int *lit_len     = malloc(32768 * sizeof(int));
    int *dist_symbol = malloc(32768 * sizeof(int));
    int *dist_len    = malloc(32768 * sizeof(int));
    ft_bzero(lit_symbol,  32768 * sizeof(int));
    ft_bzero(lit_len,     32768 * sizeof(int));
    ft_bzero(dist_symbol, 32768 * sizeof(int));
    ft_bzero(dist_len,    32768 * sizeof(int));
    build_meta_tree(HLIT, HDIST, HCLEN, bitReader, lit_symbol, lit_len, dist_symbol, dist_len);
    read_compressed_datas(buf, buf_len, max_len, bitReader, lit_symbol, lit_len, dist_symbol, dist_len);
    free(lit_symbol);
    free(lit_len);
    free(dist_symbol);
    free(dist_len);
    return (1);
}

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

        if (btype == 1)
        {
            if (!huffman_fixed(out_buf, &out_len, alloc_size, &bitReader))
                return (0);
        }
        else if (btype == 2)
        {
            if (!huffman_dynamic(out_buf, &out_len, alloc_size, &bitReader))
                return (0);
        }
        else if (btype == 0)
        {
            if (!huffman_uncompressed(out_buf, &out_len, &bitReader))
                return (0);
        }
        else
        {
            ft_dprintf(STDERR_FILENO, "BTYPE 3 invalide\n");
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