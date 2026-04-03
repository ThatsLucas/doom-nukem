/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:59:06 by aabouyaz          #+#    #+#             */
/*   Updated: 2025/05/27 11:28:58 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_hex(unsigned long long nbr, int caps, int *add)
{
	char	*dict;
	char	c;

	if (!caps)
		dict = "0123456789abcdef";
	else
		dict = "0123456789ABCDEF";
	c = dict[nbr % 16];
	if (nbr / 16)
		put_hex(nbr / 16, caps, add);
	*add = *add + ft_putchar(c);
}

void	ft_putaddr(void *point, int *add)
{
	unsigned long long	addr;

	addr = (unsigned long long)point;
	if (addr == 0)
	{
		write(1, "(nil)", 5);
		*add = *add + 5;
		return ;
	}
	*add = *add + ft_putstr("0x");
	put_hex(addr, 0, add);
}
