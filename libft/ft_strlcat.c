/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:06:54 by edurance          #+#    #+#             */
/*   Updated: 2025/07/13 18:41:48 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_strlcat(char *dst, const char *src, unsigned long siz)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	lendest;

	i = ft_strlen(dst);
	j = 0;
	lendest = i;
	if (siz <= lendest)
		return (siz + ft_strlen(src));
	while (i < siz - 1 && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (lendest + ft_strlen(src));
}
