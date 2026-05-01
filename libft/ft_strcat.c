/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:44:00 by edurance          #+#    #+#             */
/*   Updated: 2026/05/01 15:51:09 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

unsigned long	ft_strcat(char *dst, const char *src)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	lendest;

	i = ft_strlen(dst);
	j = 0;
	lendest = i;
	while (src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (lendest + ft_strlen(src));
}
