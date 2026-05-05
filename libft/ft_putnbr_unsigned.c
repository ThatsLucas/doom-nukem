/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:56:12 by edurance          #+#    #+#             */
/*   Updated: 2026/05/01 15:31:27 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_unsigned(unsigned int nbr)
{
	char	c;
	int		len;

	len = 0;
	if (nbr > 9)
		len += ft_putnbr_unsigned(nbr / 10);
	c = nbr % 10 + '0';
	len += ft_putchar_fd(c, 1);
	return (len);
}

int	ft_putunbr_fd(unsigned int nbr, int fd)
{
	char	c;
	int		len;

	len = 0;
	if (nbr > 9)
		len += ft_putunbr_fd(nbr / 10, fd);
	c = nbr % 10 + '0';
	len += ft_putchar_fd(c, fd);
	return (len);
}
