/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:23:06 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/09/23 15:49:39 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_long(long n, int fd)
{
	char	c;
	int		res;

	res = 0;
	if (n < 0)
	{
		res += write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		res += write_long(n / 10, fd);
	c = '0' + (n % 10);
	res += write(fd, &c, 1);
	return (res);
}

static int	count_digits(long n)
{
	int	c;

	c = 1;
	while (n >= 10)
	{
		n /= 10;
		c++;
	}
	return (c);
}

int	ft_putfloat(float num, int fd)
{
	long	int_part;
	long	frac_part;
	float	frac;
	int		res;
	int		i;

	res = 0;
	if (num < 0)
	{
		res += write(fd, "-", 1);
		num = -num;
	}
	int_part = (long)num;
	frac = num - (float)int_part;
	i = 0;
	while (i++ < 6)
		frac *= 10.0f;
	frac_part = (long)(frac + 0.5f);
	if (frac_part >= 1000000)
	{
		int_part += 1;
		frac_part -= 1000000;
	}
	res += write_long(int_part, fd);
	res += write(fd, ".", 1);
	i = count_digits(frac_part);
	while (i++ < 6)
		res += write(fd, "0", 1);
	res += write_long(frac_part, fd);
	return (res);
}
