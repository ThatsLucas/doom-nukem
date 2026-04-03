/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:48:40 by edurance          #+#    #+#             */
/*   Updated: 2025/09/02 12:18:02 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*res;
	long	nb;
	int		nlen;

	nlen = ft_intlen(n);
	nb = (long)n;
	res = malloc(sizeof(char) * nlen + 1);
	if (!res)
		return (NULL);
	if (nb == 0)
		res[0] = '0';
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	res[nlen] = '\0';
	nlen--;
	while (nb > 0)
	{
		res[nlen] = nb % 10 + '0';
		nb = nb / 10;
		nlen--;
	}
	return (res);
}
