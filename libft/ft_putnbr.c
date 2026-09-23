/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:27:12 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/09/23 15:52:48 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long long n, int *add)
{
	if (n == LLONG_MIN)
	{
		*add = *add + ft_putstr("-9223372036854775808");
		return ;
	}
	if (n < 0)
	{
		*add = *add + ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10, add);
	*add = *add + ft_putchar((n % 10) + '0');
}

void	ft_sputnbr(char *str, int n, size_t size)
{
	long	nb;
	int		nlen;

	nlen = ft_intlen(n);
	if (!str)
		return ;
	if ((size_t)nlen + 1 > size)
	{
		if (size > 0)
			str[0] = '\0';
		return ;
	}
	nb = (long)n;
	str[nlen] = 0;
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

	return ;
}
