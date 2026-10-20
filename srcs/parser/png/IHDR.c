/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHDR.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:06:48 by root-             #+#    #+#             */
/*   Updated: 2026/08/12 16:00:16 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/PNG.h"

/* Lit l’en-tête du bloc IHDR. */
static int read_IHDR_header(int fd, t_IHDR *headerIHDR)
{
    ssize_t bytes_read = read(fd, &headerIHDR->chunklen, sizeof(headerIHDR->chunklen));
    if(bytes_read != sizeof(headerIHDR->chunklen))
        return (-1);

    bytes_read = read(fd, &headerIHDR->chunktype, sizeof(headerIHDR->chunktype));
    if(bytes_read != sizeof(headerIHDR->chunktype))
        return (-1);
    // headerIHDR->chunktype = big_endian_to_little_endian(headerIHDR->chunktype);
    headerIHDR->chunklen = big_endian_to_little_endian(headerIHDR->chunklen);
    if (ft_memcmp(&headerIHDR->chunktype, "IHDR", 4))
    {
        ft_dprintf(STDERR_FILENO, "Invalid chunktype %d\n", headerIHDR->chunktype);
        return (-1);
    }
    return (0);
}

/* Lit toutes les données du bloc IHDR. */
static int read_all_IHDR_datas(t_png *pngFile)
{
    int fd = pngFile->fd;

    ssize_t bytes_read = read(fd, &pngFile->IHDR.w, sizeof(pngFile->IHDR.w));
    if(bytes_read != sizeof(pngFile->IHDR.w))
        return (-1);

    bytes_read = read(fd, &pngFile->IHDR.h, sizeof(pngFile->IHDR.h));
    if(bytes_read != sizeof(pngFile->IHDR.h))
        return (-1);

    bytes_read = read(fd, &pngFile->IHDR.bit_depth, sizeof(pngFile->IHDR.bit_depth));
    if(bytes_read != sizeof(pngFile->IHDR.bit_depth))
        return (-1);

    bytes_read = read(fd, &pngFile->IHDR.color_type, sizeof(pngFile->IHDR.color_type));
    if(bytes_read != sizeof(pngFile->IHDR.color_type))
        return (-1);

    bytes_read = read(fd, &pngFile->IHDR.compression_method, sizeof(pngFile->IHDR.compression_method));
    if(bytes_read != sizeof(pngFile->IHDR.compression_method))
        return (-1);

    bytes_read = read(fd, &pngFile->IHDR.filter_method, sizeof(pngFile->IHDR.filter_method));
    if(bytes_read != sizeof(pngFile->IHDR.filter_method))
        return (-1);

    bytes_read = read(fd, &pngFile->IHDR.interlace_method, sizeof(pngFile->IHDR.interlace_method));
    if(bytes_read != sizeof(pngFile->IHDR.interlace_method))
        return (-1);

    pngFile->w = pngFile->IHDR.w;
    pngFile->h = pngFile->IHDR.h;
    return (0);
}

/* Lit les informations de contrôle CRC. */
static int read_crc_info(t_IHDR *headerIHDR, int fd)
{
    int ret = 0;
    ret = read(fd, &headerIHDR->crc, sizeof(headerIHDR->crc));
    return (ret);
}

/* Convertit les valeurs au format petit-boutiste. */
static void convert_all_value_to_little_endian(t_png *pngFile)
{
    pngFile->w = big_endian_to_little_endian(pngFile->w);
    pngFile->h = big_endian_to_little_endian(pngFile->h);
}

/* Lit et valide le bloc IHDR. */
int find_png_IHDR(t_IHDR *headerIHDR, t_png *pngFile)
{
    if (read_IHDR_header(pngFile->fd, headerIHDR) < 0)
    {
        ft_dprintf(STDERR_FILENO, "Invalid IHDR Header!\n");
        return (0);
    }

    if (read_all_IHDR_datas(pngFile) < 0)
    {
        ft_dprintf(STDERR_FILENO,"Invalid IHDR Datas!\n");
        return (0);
    }

    if (read_crc_info(headerIHDR, pngFile->fd) == -1)
    {
        ft_dprintf(STDERR_FILENO, "Invalid IHDR CRC!\n");
        return (0);
    }
    convert_all_value_to_little_endian(pngFile);
    if (headerIHDR->color_type == 2)
        headerIHDR->bytes_per_pixel = 3;
    else if (headerIHDR->color_type == 6)
        headerIHDR->bytes_per_pixel = 4;
    else if (headerIHDR->color_type == 0)
        headerIHDR->bytes_per_pixel = 1;
    else if (headerIHDR->color_type == 4)
        headerIHDR->bytes_per_pixel = 2;
    return (1);
}