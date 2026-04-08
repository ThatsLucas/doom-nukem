/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDAT.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root- <root-@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:02:08 by root-             #+#    #+#             */
/*   Updated: 2026/04/08 17:34:19 by root-            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser/PNG.h"

static unsigned int is_IDAT_or_IEND(__uint32_t type)
{
    if (!ft_memcmp(&type, "IDAT", 4))
        return (1);
    if (!ft_memcmp(&type, "IEND", 4))
        return (2);
    return (0);
}

int find_all_IDAT(t_png *pngFile)
{
    t_IDAT_LIST *idata = malloc(sizeof(t_IDAT_LIST));
    t_IDAT_LIST *tmp_idata = idata;
    int endHeaderFound = 0;

    while (!endHeaderFound)
    {
        __uint32_t len;
        __uint32_t type;

        ssize_t bytes_read = read(pngFile->fd, &len, sizeof(len));
        if (bytes_read != sizeof(len))
            return (-1);
            
        bytes_read = read(pngFile->fd, &type, sizeof(type));
        if (bytes_read != sizeof(type))
            return (-1);

        type = is_IDAT_or_IEND(type);
        if (type == 1)
        {
            tmp_idata->datas = malloc(sizeof(t_IDAT));
            //todo
        }
        else
        {
            lseek(pngFile->fd, len, SEEK_CUR);
        }
    }
    return (0);
}