/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:00:00 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/02 11:31:00 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sputnbr(char *str, int n, size_t size)
{
	long	nb;
	int		nlen;

	if (!str)
		return ;
	nlen = ft_intlen(n);
	if ((size_t)nlen + 1 > size)
	{
		if (size > 0)
			str[0] = '\0';
		return ;
	}
	nb = (long)n;
	str[nlen] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	nlen--;
	while (nb > 0)
	{
		str[nlen] = nb % 10 + '0';
		nb /= 10;
		nlen--;
	}
}
