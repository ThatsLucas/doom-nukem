/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:09:50 by root-             #+#    #+#             */
/*   Updated: 2026/04/10 11:53:18 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#define HUFFMAN_UNCOMPRESSED 0
#define HUFFMAN_FIXED 1
#define HUFFMAN_DYNAMIC 2

/*IHDR*/
#define RGB 2
#define RGBA 6
#define GRAYSCALE 0
#define GRAYSCALE_ALPHA 4

typedef struct s_huffman_dy
{
    __uint8_t BTYPE;
    __uint8_t BFINAL;
}              t_huffman_dy;

#endif