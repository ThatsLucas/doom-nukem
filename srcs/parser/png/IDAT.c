/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDAT.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:02:08 by root-             #+#    #+#             */
/*   Updated: 2026/05/05 12:46:44 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/PNG.h"

/* Libère les données du bloc IDAT. */
static void free_idat(t_IDAT *idat)
{
    free(idat->datas);
    free(idat);
    idat = NULL;
}

/* Vérifie si le bloc PNG est IDAT ou IEND. */
static int is_IDAT_or_IEND(__uint32_t type)
{
    if (!ft_memcmp(&type, "IDAT", 4))
        return (1);
    if (!ft_memcmp(&type, "IEND", 4))
        return (2);
    return (0);
}

/* Remplit la structure des données IDAT. */
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

/* Lit la longueur et le type du prochain bloc PNG. */
static int read_chunk_header(int fd, __uint32_t *len, __uint32_t *type)
{
    ssize_t bytes_read = read(fd, len, sizeof(*len));
    if (bytes_read != sizeof(*len))
    {
        ft_dprintf(STDERR_FILENO, "returned in invalid len\n");
        return (0);
    }
    *len = big_endian_to_little_endian(*len);

    bytes_read = read(fd, type, sizeof(*type));
    if (bytes_read != sizeof(*type))
    {
        ft_dprintf(STDERR_FILENO, "invalid type size\n");
        return (0);
    }
    return (1);
}

/* Ajoute les données du bloc IDAT au tampon. */
static void append_idat(t_IDAT **head, t_IDAT *node)
{
    t_IDAT *last;

    node->next = NULL;
    if (!*head)
    {
        *head = node;
        return ;
    }
    last = *head;
    while (last->next)
        last = last->next;
    last->next = node;
}

/* Ignore un bloc PNG inconnu facultatif. */
static int skip_unknown_chunk(int fd, __uint32_t type, __uint32_t len)
{
    char *c = (char *)&type;

    if (!(c[0] & 0x20))
    {
        ft_dprintf(STDERR_FILENO, "[PNG PARSER] - Error, mandatory unknown header found (%c), can't diplay the image\n", c);
        return (0);
    }
    lseek(fd, len + 4, SEEK_CUR);
    return (1);
}

/* Lit tous les blocs IDAT du fichier PNG. */
t_IDAT * find_all_IDAT(t_png *pngFile)
{
    t_IDAT *head = NULL;
    t_IDAT *tmp_idata;
    __uint32_t len;
    __uint32_t type;

    while (1)
    {
        if (!read_chunk_header(pngFile->fd, &len, &type))
        {
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
            append_idat(&head, tmp_idata);
        }
        else if (typeRet == 2)
            break;
        else if (!skip_unknown_chunk(pngFile->fd, type, len))
        {
            free_idat_list(head);
            return head;
        }
    }
    return (head);
}
