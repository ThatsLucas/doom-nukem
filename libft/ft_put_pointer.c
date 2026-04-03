/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:27:55 by edurance          #+#    #+#             */
/*   Updated: 2025/08/09 15:47:15 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_hexa(unsigned long long nb, int *entier)
{
	char	c;
	char	*base;

	base = "0123456789abcdef";
	c = base[nb % 16];
	if (nb / 16 > 0)
		ft_put_hexa(nb / 16, entier);
	*entier += ft_putchar_fd(c, 1);
}

int	ft_put_pointer(void *pointer)
{
	unsigned long long	ptr;
	int					res;

	res = 0;
	ptr = (unsigned long long)pointer;
	if (ptr == 0)
		return (ft_putstr_fd("(nil)", 1));
	res += ft_putchar_fd('0', 1);
	res += ft_putchar_fd('x', 1);
	ft_put_hexa(ptr, &res);
	return (res);
}
