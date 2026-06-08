/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:33:57 by lle-duc           #+#    #+#             */
/*   Updated: 2026/06/08 12:17:09 by edurance         ###   ########.fr       */
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

void *process_png(void *pngStruct)
{
    t_IDAT *IDATS;
    t_png *pngFile = (t_png *)pngStruct;
    pngFile->buf = NULL;
    pngFile->fd = open_png_file(pngFile->path);
    if (!pngFile->fd)
    {
        free(pngFile->path);
        pngFile->path = NULL;
        return ((void *)(long)0);
    }
    find_png_header(pngFile);
    find_png_IHDR(&pngFile->IHDR, pngFile);
    IDATS = find_all_IDAT(pngFile);
	close(pngFile->fd);
    if (!IDATS)
    {
        ft_dprintf(STDERR_FILENO, "Issue parsing IDATS, can't read img\n");
        free(pngFile->path);
        pngFile->path = NULL;
        return ((void *)(long)0);
    }
    __uint8_t *mergedBuffer = merge_all_buffers(IDATS);
    if (!mergedBuffer)
    {
        ft_dprintf(STDERR_FILENO, "Issue concatening IDATS, can't read img\n");
        free_idat_list(IDATS);
        free(pngFile->path);
        pngFile->path = NULL;
        return ((void *)(long)0);
    }
    parse_deflate_blocs(pngFile, mergedBuffer, get_total_compressed_size(IDATS));
    free(mergedBuffer);
    free_idat_list(IDATS);
    free(pngFile->path);
    pngFile->path = NULL;
    return ((void *)(long)1);
}
