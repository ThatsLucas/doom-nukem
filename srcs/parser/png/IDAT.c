/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDAT.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:02:08 by root-             #+#    #+#             */
/*   Updated: 2026/05/01 16:06:24 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser/PNG.h"

__uint64_t get_total_compressed_size(t_IDAT *lst)
{
    __uint64_t size = 0;
    
    while (lst)
    {
        size += lst->chunklen;
        lst = lst->next;
    }
    return size;
}

__uint8_t *merge_all_buffers(t_IDAT *lst)
{
    __uint64_t compressedSize = get_total_compressed_size(lst);
    __uint8_t *compressedBuffer = malloc(sizeof(__uint8_t) * compressedSize);
    if (!compressedBuffer)
    {
        perror("compressed buffer allocation:");
        return NULL;
    }
    __uint64_t i = 0;
    while(lst)
    {
        ft_memmove(compressedBuffer + i, lst->datas, lst->chunklen);
        i += lst->chunklen;
        lst = lst->next;
    }
    return compressedBuffer;
}

void free_idat_list(t_IDAT *lst)
{
    while (lst)
    {
        t_IDAT *tmp = lst->next;
        free(lst->datas);
        free(lst);
        lst = tmp;
    }
    lst = NULL;
}

static void free_idat(t_IDAT *idat)
{
    free(idat->datas);
    free(idat);
    idat = NULL;
}

static int is_IDAT_or_IEND(__uint32_t type)
{
    if (!ft_memcmp(&type, "IDAT", 4))
        return (1);
    if (!ft_memcmp(&type, "IEND", 4))
        return (2);
    return (0);
}


static int fill_idat_struct(int fd, t_IDAT *idat, __uint32_t len)
{
    idat->datas = NULL;
    if (!len)
    {
        free_idat(idat);
        return (0);
    }

    idat->datas = malloc(len);
    ssize_t bytes_read = read(fd, idat->datas, len);
    if (bytes_read != len)
    {
        perror("idat fill:");
        free_idat(idat);
        return (0);
    }
    
    idat->chunklen = len;
    
    bytes_read = read(fd, &idat->crc, sizeof(idat->crc));
    if (bytes_read != (ssize_t)sizeof(idat->crc))
    {
        perror("crc:");
        free_idat(idat);
        return (0);
    }

    idat->next = NULL;
    return (1);
}

t_IDAT * find_all_IDAT(t_png *pngFile)
{
    t_IDAT *head = NULL;
    t_IDAT *tmp_idata;
    // ft_printf("\n");
    while (1)
    {
        __uint32_t len;
        __uint32_t type;

        ssize_t bytes_read = read(pngFile->fd, &len, sizeof(len));
        if (bytes_read != sizeof(len))
        {
            ft_dprintf(STDERR_FILENO, "returned in invalid len\n");
            free_idat_list(head);
            return head;
        }
        len = big_endian_to_little_endian(len);

        bytes_read = read(pngFile->fd, &type, sizeof(type));
        if (bytes_read != sizeof(type))
        {
            ft_dprintf(STDERR_FILENO, "invalid type size\n");

            free_idat_list(head);
            return head;
        }

        int typeRet = is_IDAT_or_IEND(type);
        if (typeRet == 1)
        {
            tmp_idata = malloc(sizeof(t_IDAT));
            if(!fill_idat_struct(pngFile->fd, tmp_idata, len))
            {
                free_idat_list(head);
                return NULL;
            }
            tmp_idata->next = NULL;
            if (!head)
                head = tmp_idata;
            else
            {
                t_IDAT *last = head;
                while (last->next)
                    last = last->next;
                last->next = tmp_idata;
            }
            // ft_printf("[PNG PARSER] - just read an IDAT...\n");
        }
        else if (typeRet == 2)
        {
            // ft_printf("[PNG PARSER] - end of image found returning...\n");
            break;
        }
        else
        {
            char *c = (char *)&type;
            if (!(c[0] & 0x20))
            {
                free_idat_list(head);
                ft_dprintf(STDERR_FILENO, "[PNG PARSER] - Error, mandatory unknown header found (%c), can't diplay the image\n", c);
                return head;
            }
            lseek(pngFile->fd, len + 4, SEEK_CUR);
        }
    }
    return (head);
}