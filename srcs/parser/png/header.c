/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root- <root-@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:13:34 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/07 16:34:17 by root-            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser/PNG.h"

static int check_header_validity(char *buf)
{
    // "137 80 78 71 13 10 26 10" = char chelou P N G char chelou
    unsigned char requiredHeader[8] = {137, 80, 78, 71, 13, 10, 26, 10};
    
    for(int i = 0; i < 8; i++)
    {
        if (requiredHeader[i] != buf[i])
            return (0);
    }
    return (1);
}

int find_png_header(t_png *pngFile)
{
    t_readPNG readDatas = read_nbytes(pngFile->fd, 8);
    readDatas.buf[readDatas.nbytes] = '\0';
    
    if (check_header_validity(readDatas.buf) == 0)
        ft_printf("This file has a valid png header!\n");
    else
        ft_printf("This file has not valid png header!\n");
    return (1);
}

int find_next_chunk()
{
    //todo
    return 0;
}