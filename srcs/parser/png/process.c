/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:33:57 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/10 23:40:48 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser/PNG.h"


static int open_png_file(char *path)
{
    int pngFile = open(path, O_RDONLY);

    if (pngFile < 0)
    {
        perror("open_png_file:");
        return  (0);
    }
    return (pngFile);
}

t_readPNG read_nbytes(int pngFile, int nbytes)
{
    t_readPNG readDatas;
    readDatas.nbytes = read(pngFile, readDatas.buf, nbytes);
    return (readDatas);
}

int process_png(t_png *pngFile, char *path)
{
    t_IDAT *IDATS;

    pngFile->fd = open_png_file(path);
    if (!pngFile->fd)
        return (0);
    find_png_header(pngFile);
    find_png_IHDR(&pngFile->IHDR, pngFile);
    IDATS = find_all_IDAT(pngFile);
    if (!IDATS)
    {
        ft_printf("Issue parsing IDATS, can't read img\n");
        return (0);
    }
    __uint8_t *mergedBuffer = merge_all_buffers(IDATS);
    if (!mergedBuffer)
    {
        ft_printf("Issue concatening IDATS, can't read img\n");
        free_idat_list(IDATS);
        return (0);
    }
    parse_deflate_blocs(pngFile, mergedBuffer, get_total_compressed_size(IDATS));
    free(mergedBuffer);
    free_idat_list(IDATS);
    return (1);
}