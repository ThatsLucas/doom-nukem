/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:27:53 by aabouyaz          #+#    #+#             */
/*   Updated: 2025/07/09 12:40:53 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_int_table(int *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("value [%d]\t=\t'%d'\n", i, tab[i]);
		i++;
	}
}

void	print_str_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("value [%d]\t=\t'%s'\n", i, tab[i]);
		i++;
	}
}

int	count_elem(void **tab)
{
	int	count;

	count = 0;
	while (tab && tab[count])
		count++;
	return (count);
}
