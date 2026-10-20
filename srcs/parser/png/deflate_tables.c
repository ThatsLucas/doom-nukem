/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deflate_tables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:24:26 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:24:26 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/PNG.h"
#include "parser/huffman.h"

/* Construit la table Huffman canonique à partir des longueurs de codes. */
void build_code_table(int *lengths, __uint32_t count, int *table_symbol, int *table_len)
{
    int frequecy[16] = {0};
    int first_code[16] = {0};

    for (__uint32_t i = 0; i < count; i++)
        frequecy[lengths[i]]++;
    for (__uint32_t i = 1; i <= 14; i++)
        first_code[i+1] = (first_code[i] + frequecy[i]) << 1;
    for (__uint32_t i = 0; i < count; i++)
    {
        if (lengths[i] > 0)
        {
            table_symbol[first_code[lengths[i]]] = i;
            table_len[first_code[lengths[i]]]    = lengths[i];
            first_code[lengths[i]]++;
        }
    }
}

/* Ajoute une valeur au nombre de répétitions indiqué. */
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

/* Construit la table des longueurs de codes Huffman. */
static void build_code_length_table(__uint32_t HCLEN, t_bitreader *bitReader, int *table_symbol, int *table_len)
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

    for (int i = 0; i < 19; i++)
    {
        if (code_len[i] > 0)
        {
            table_symbol[first_code[code_len[i]]] = i;
            table_len[first_code[code_len[i]]] = code_len[i];
            first_code[code_len[i]] += 1;
        }
    }
}

/* Lit les longueurs des codes des arbres Huffman. */
static int *read_tree_lengths(__uint32_t HLIT, __uint32_t HDIST, t_bitreader *bitReader, int *table_symbol, int *table_len)
{
    int *lengths = malloc((HLIT + HDIST)  * sizeof(int));
    ft_bzero(lengths,  (HLIT + HDIST) * sizeof(int));

    for (__uint32_t i = 0; i < HLIT + HDIST; i++)
    {
        int sym = read_symbol(bitReader, table_symbol, table_len, 7);
        if (sym >= 0 && sym <= 15)
            lengths[i] = sym;
        else if (sym == 16)
            push_value_n_times(lengths, &i, HLIT, HDIST, 3, 2, bitReader, lengths[i - 1]);
        else if (sym == 17)
            push_value_n_times(lengths, &i, HLIT, HDIST, 3, 3, bitReader, 0);
        else if (sym == 18)
            push_value_n_times(lengths, &i, HLIT, HDIST, 11, 7, bitReader, 0);
    }
    return (lengths);
}

/* Construit les tables Huffman d’un bloc dynamique. */
void build_meta_tree(__uint32_t HLIT, __uint32_t HDIST, __uint32_t HCLEN, t_bitreader *bitReader, int *lit_symbol, int *lit_len, int *dist_symbol, int *dist_len)
{
    int table_symbol[128] = {0};
    int table_len[128] = {0};
    int *lengths;

    build_code_length_table(HCLEN, bitReader, table_symbol, table_len);
    lengths = read_tree_lengths(HLIT, HDIST, bitReader, table_symbol, table_len);
    build_code_table(lengths, HLIT, lit_symbol, lit_len);
    build_code_table(lengths + HLIT, HDIST, dist_symbol, dist_len);
    free(lengths);
}
