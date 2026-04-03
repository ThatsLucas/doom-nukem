/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:27:12 by aabouyaz          #+#    #+#             */
/*   Updated: 2025/05/27 11:28:20 by aabouyaz         ###   ########.fr       */
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
