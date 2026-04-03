/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:51:39 by edurance          #+#    #+#             */
/*   Updated: 2025/07/13 18:42:30 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	lentrim(const char *s1, const char *set)
{
	int				count;
	unsigned long	i;
	unsigned long	j;

	count = 0;
	i = 0;
	j = (int)ft_strlen(s1) - 1;
	while (ft_isinset(s1[i], set))
	{
		count++;
		i++;
	}
	if (i == ft_strlen(s1))
		return (0);
	while (ft_isinset(s1[j], set))
	{
		count++;
		j--;
	}
	return (ft_strlen(s1) - count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (lentrim(s1, set) + 1));
	if (!res)
		return (NULL);
	while (ft_isinset(s1[i], set))
		i++;
	while (j < lentrim(s1, set))
	{
		res[j] = s1[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}
