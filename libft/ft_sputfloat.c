/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sputfloat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 15:49:59 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/09/23 15:53:05 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	long_len(long n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static long	float_value(float *num, int *negative)
{
	long	value;

	*negative = *num < 0;
	if (*negative)
		*num = -*num;
	value = (long)(*num * 1000.0f + 0.5f);
	return (value);
}

static int	trim_fraction(long *fraction)
{
	int	len;

	len = 3;
	while (*fraction && *fraction % 10 == 0)
	{
		*fraction /= 10;
		len--;
	}
	if (*fraction == 0)
		return (0);
	return (len);
}

static int	float_len(long integer, int fraction_len, int negative)
{
	int	len;

	len = negative + long_len(integer);
	if (fraction_len)
		len += 1 + fraction_len;
	return (len);
}

static int	write_fraction(char *str, int index, long fraction, int len)
{
	int	written;

	written = 0;
	while (fraction)
	{
		str[index--] = (fraction % 10) + '0';
		fraction /= 10;
		written++;
	}
	while (written++ < len)
		str[index--] = '0';
	return (index);
}

static int	write_integer(char *str, int index, long integer)
{
	if (integer == 0)
		str[index--] = '0';
	while (integer)
	{
		str[index--] = (integer % 10) + '0';
		integer /= 10;
	}
	return (index);
}

void	ft_sputfloat(char *str, float num, size_t size)
{
	long	int_part, frac_part, value;
	int		negative, len, index, frac_len;

	if (!str || size == 0)
		return ;
	value = float_value(&num, &negative);
	int_part = value / 1000;
	frac_part = value % 1000;
	frac_len = trim_fraction(&frac_part);
	len = float_len(int_part, frac_len, negative);
	if ((size_t)len + 1 > size)
	{
		str[0] = '\0';
		return ;
	}
	index = len;
	str[index--] = '\0';
	if (frac_part)
	{
		index = write_fraction(str, index, frac_part, frac_len);
		str[index--] = '.';
	}
	index = write_integer(str, index, int_part);
	if (negative)
		str[index] = '-';
}
