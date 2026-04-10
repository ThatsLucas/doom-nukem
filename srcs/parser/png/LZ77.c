/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LZ77.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:39:24 by lucas             #+#    #+#             */
/*   Updated: 2026/04/10 23:11:27 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser/PNG.h"

void lz77(__uint8_t *buf, __uint32_t *buf_len, size_t max_len, t_bitreader *bitReader, int sym, int *dist_symbol, int *dist_len)
{
    int length_table[29][2] = { //RFC 1951
        {3, 0},  {4, 0},  {5, 0},  {6, 0},  {7, 0},
        {8, 0},  {9, 0},  {10, 0}, {11, 1}, {13, 1},
        {15, 1}, {17, 1}, {19, 2}, {23, 2}, {27, 2},
        {31, 2}, {35, 3}, {43, 3}, {51, 3}, {59, 3},
        {67, 4}, {83, 4}, {99, 4}, {115, 4},{131, 5},
        {163, 5},{195, 5},{227, 5},{258, 0}
    };

    int dist_table[30][2] = {//RFC 1951
        {1, 0},    {2, 0},    {3, 0},    {4, 0},    {5, 1},
        {7, 1},    {9, 2},    {13, 2},   {17, 3},   {25, 3},
        {33, 4},   {49, 4},   {65, 5},   {97, 5},   {129, 6},
        {193, 6},  {257, 7},  {385, 7},  {513, 8},  {769, 8},
        {1025, 9}, {1537, 9}, {2049, 10},{3073, 10}, {4097, 11},
        {6145, 11},{8193, 12},{12289, 12},{16385, 13},{24577, 13}
    };

    if (sym < 257 || sym > 285)
    {
        ft_printf("ERREUR lz77: sym invalide = %d\n", sym);
        return;
    }

    int len_base  = length_table[sym - 257][0];
    int len_extra = read_bits(bitReader, length_table[sym - 257][1]);
    int len = len_base + len_extra; // combien de byte la sequence que jvais copier mesure en taille

    sym = read_symbol(bitReader, dist_symbol, dist_len, 15);
    int dist_base = dist_table[sym][0];
    int dist_extra = read_bits(bitReader, dist_table[sym][1]);
    int distance = dist_base + dist_extra;

    for (int i = 0; i < len; i++) // dedicace à felix fallait être là
    {
        if (*buf_len + i >= max_len || (__uint32_t)distance > *buf_len + i)
        {
            ft_printf("lz77: bruhhhhhhhhhhh\n"); //si ca arrive c la merde
            return;
        }

        buf[*buf_len + i] = buf[*buf_len - distance + i];
    }
    *buf_len += len;
}