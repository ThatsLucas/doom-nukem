/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDAT_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:25:45 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:25:45 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/PNG.h"

/* Calcule la taille totale des données IDAT. */
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

/* Concatène les données de tous les blocs IDAT. */
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

/* Libère la liste des blocs IDAT. */
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
