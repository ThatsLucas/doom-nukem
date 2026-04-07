/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root- <root-@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:33:57 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/07 11:37:44 by root-            ###   ########.fr       */
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

int process_png(char *path)
{
    t_png pngFile;

    pngFile.fd = open_png_file(path);
    if (!pngFile.fd)
        return (0);
    find_png_header(&pngFile);
    find_png_IHDR(&pngFile);
    return (1);
}