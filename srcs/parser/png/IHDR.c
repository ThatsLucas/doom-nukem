/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHDR.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root- <root-@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:06:48 by root-             #+#    #+#             */
/*   Updated: 2026/04/07 13:51:27 by root-            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser/PNG.h"

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
        ft_printf("Invalid chunktype %d\n", headerIHDR->chunktype);
        return (-1);
    }
    return (0);
}

static int read_all_IHDR_datas(t_png *pngFile)
{
    int fd = pngFile->fd;

    ssize_t bytes_read = read(fd, &pngFile->w, sizeof(pngFile->w));
    if(bytes_read != sizeof(pngFile->w))
        return (-1);

    bytes_read = read(fd, &pngFile->h, sizeof(pngFile->h));
    if(bytes_read != sizeof(pngFile->h))
        return (-1);

    bytes_read = read(fd, &pngFile->bit_depth, sizeof(pngFile->bit_depth));
    if(bytes_read != sizeof(pngFile->bit_depth))
        return (-1);

    bytes_read = read(fd, &pngFile->color_type, sizeof(pngFile->color_type));
    if(bytes_read != sizeof(pngFile->color_type))
        return (-1);

    bytes_read = read(fd, &pngFile->compression_method, sizeof(pngFile->compression_method));
    if(bytes_read != sizeof(pngFile->compression_method))
        return (-1);

    bytes_read = read(fd, &pngFile->filter_method, sizeof(pngFile->filter_method));
    if(bytes_read != sizeof(pngFile->filter_method))
        return (-1);

    bytes_read = read(fd, &pngFile->interlace_method, sizeof(pngFile->interlace_method));
    if(bytes_read != sizeof(pngFile->interlace_method))
        return (-1);
    return (0);
}

// read juste pas besoin de check l'integrite normalement
static int read_crc_info(t_IHDR headerIHDR, int fd)
{
    int ret = 0;
    ret = read(fd, &headerIHDR.crc, sizeof(headerIHDR.crc));
    return (ret);
}

static void convert_all_value_to_little_endian(t_png *pngFile)
{
    pngFile->w = big_endian_to_little_endian(pngFile->w);
    pngFile->h = big_endian_to_little_endian(pngFile->h);
}

int find_png_IHDR(t_png *pngFile)
{
    t_IHDR headerIHDR;

    if (read_IHDR_header(pngFile->fd, &headerIHDR) < 0)
    {
        ft_printf("Invalid IHDR Header!\n");
        return (0);
    }

    if (read_all_IHDR_datas(pngFile) < 0)
    {
        ft_printf("Invalid IHDR Datas!\n");
        return (0);
    }

    if (read_crc_info(headerIHDR, pngFile->fd) == -1)
    {
        ft_printf("Invalid IHDR CRC!\n");
        return (0);
    }
    convert_all_value_to_little_endian(pngFile);
    printf("image w = %d h = %d", pngFile->w, pngFile->h);
    return (1);
}