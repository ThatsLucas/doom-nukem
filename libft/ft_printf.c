/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:39:06 by edurance          #+#    #+#             */
/*   Updated: 2025/07/13 18:40:03 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	goodtype(char c)
{
	char	*types;
	int		i;

	types = "cspdiuxX%";
	i = 0;
	while (types[i])
	{
		if (c == types[i])
			return (1);
		i++;
	}
	return (0);
}

static int	find_type(char type, va_list args)
{
	int	len;

	len = 0;
	if (type == 'c')
		len += ft_putchar_fd(va_arg(args, int), 1);
	else if (type == 's')
		len += ft_putstr_fd(va_arg(args, char *), 1);
	else if (type == 'p')
		len += ft_put_pointer(va_arg(args, void *));
	else if (type == 'd' || type == 'i')
		len += ft_putnbr_fd(va_arg(args, int), 1);
	else if (type == 'u')
		len += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (type == 'x')
		len += ft_hexa(va_arg(args, long), 0);
	else if (type == 'X')
		len += ft_hexa(va_arg(args, long), 1);
	else if (type == '%')
		len += ft_putchar_fd('%', 1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && goodtype(str[i + 1]))
		{
			len += find_type(str[i + 1], args);
			i = i + 2;
		}
		else
		{
			len += ft_putchar_fd(str[i], 1);
			i++;
		}
	}
	va_end(args);
	return (len);
}
