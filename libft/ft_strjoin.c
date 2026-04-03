/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:25:12 by edurance          #+#    #+#             */
/*   Updated: 2025/08/20 10:53:01 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	lenmalloc(const char *s1, const char *s2)
{
	return (ft_strlen(s1) + ft_strlen(s2) + 1);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned long	i;
	unsigned long	j;
	char			*res;

	res = malloc(lenmalloc(s1, s2) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	return (res);
}
