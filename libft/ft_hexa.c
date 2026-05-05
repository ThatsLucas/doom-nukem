/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:21:32 by edurance          #+#    #+#             */
/*   Updated: 2026/05/01 15:32:38 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexa(long nbr, int maj)
{
	char			c;
	char			*base;
	unsigned int	nb;
	int				len;

	len = 0;
	nb = (unsigned int)nbr;
	if (!maj)
		base = "0123456789abcdef";
	if (maj)
		base = "0123456789ABCDEF";
	c = base[nb % 16];
	if (nb / 16 > 0)
		len += ft_hexa(nb / 16, maj);
	len += ft_putchar_fd(c, 1);
	return (len);
}

int	ft_hexa_fd(long nbr, int maj, int fd)
{
	char			c;
	char			*base;
	unsigned int	nb;
	int				len;

	len = 0;
	nb = (unsigned int)nbr;
	if (!maj)
		base = "0123456789abcdef";
	if (maj)
		base = "0123456789ABCDEF";
	c = base[nb % 16];
	if (nb / 16 > 0)
		len += ft_hexa_fd(nb / 16, maj, fd);
	len += ft_putchar_fd(c, fd);
	return (len);
}

