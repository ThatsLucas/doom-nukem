/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:27:38 by edurance          #+#    #+#             */
/*   Updated: 2026/06/23 15:19:15 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	goodtype(char c)
{
	char	*types;
	int		i;

	types = "csfpdiuxX%";
	i = 0;
	while (types[i])
	{
		if (c == types[i])
			return (1);
		i++;
	}
	return (0);
}

static int	find_type(char type, va_list args, int fd)
{
	int	len;

	len = 0;
	if (type == 'c')
		len += ft_putchar_fd(va_arg(args, int), fd);
	else if (type == 's')
		len += ft_putstr_fd(va_arg(args, char *), fd);
	else if (type == 'p')
		len += ft_put_pointer_fd(va_arg(args, void *), fd);
	else if (type == 'd' || type == 'i')
		len += ft_putnbr_fd(va_arg(args, int), fd);
	else if (type == 'f')
		len += ft_putfloat(va_arg(args, double), fd);
	else if (type == 'u')
		len += ft_putunbr_fd(va_arg(args, unsigned int), fd);
	else if (type == 'x')
		len += ft_hexa_fd(va_arg(args, long), 0, fd);
	else if (type == 'X')
		len += ft_hexa_fd(va_arg(args, long), 1, fd);
	else if (type == '%')
		len += ft_putchar_fd('%', fd);
	return (len);
}

int	ft_dprintf(int fd, const char *str, ...)
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
			len += find_type(str[i + 1], args, fd);
			i = i + 2;
		}
		else
		{
			len += ft_putchar_fd(str[i], fd);
			i++;
		}
	}
	va_end(args);
	return (len);
}
