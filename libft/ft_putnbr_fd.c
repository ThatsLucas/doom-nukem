/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:41:19 by edurance          #+#    #+#             */
/*   Updated: 2026/09/23 15:45:50 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		len;

	len = 0;
	if (n == -2147483648)
	{
		len = ft_putstr_fd("-2147483648", fd);
		return (len);
	}
	if (n < 0)
	{
		len += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
		len += ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	len += ft_putchar_fd(c, fd);
	return (len);
}
