/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:27:13 by edurance          #+#    #+#             */
/*   Updated: 2025/07/13 18:42:34 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, unsigned long len)
{
	char			*news;
	unsigned long	n;
	unsigned long	i;

	if (ft_strlen(s) <= start)
		n = 1;
	else if (len >= ft_strlen(s + start))
		n = ft_strlen(s + start) + 1;
	else
		n = len + 1;
	news = malloc(sizeof(char) * n);
	if (!news)
		return (NULL);
	news[0] = '\0';
	if (ft_strlen(s) <= start)
		return (news);
	i = 0;
	while (s[i + start] && i < len)
	{
		news[i] = s[i + start];
		i++;
	}
	news[i] = '\0';
	return (news);
}
