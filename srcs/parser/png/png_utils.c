/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:12:30 by root-             #+#    #+#             */
/*   Updated: 2026/07/17 12:59:08 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/PNG.h"

__uint32_t big_endian_to_little_endian(__uint32_t n)
{
    static const __uint32_t islittle = 0x01020304;
    if (*(__uint8_t *)&islittle == 0x01) //check si on est pas dejq en little
        return n;
    return (
        ((n & 0x000000FF) << 24) |
        ((n & 0x0000FF00) << 8)  |
        ((n & 0x00FF0000) >> 8)  |
        ((n & 0xFF000000) >> 24)
    );
}