/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:47:21 by aabouyaz          #+#    #+#             */
/*   Updated: 2025/08/14 12:49:14 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	char	*spaces;
	int		i;

	i = 0;
	spaces = " \f\n\r\t\v";
	while (spaces[i])
	{
		if (spaces[i] == c)
			return (1);
		i++;
	}
	return (0);
}
