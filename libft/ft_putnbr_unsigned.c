/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:56:12 by edurance          #+#    #+#             */
/*   Updated: 2025/07/13 18:40:59 by aabouyaz         ###   ########.fr       */
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
