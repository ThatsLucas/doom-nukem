/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:46:01 by aabouyaz          #+#    #+#             */
/*   Updated: 2025/07/13 18:41:15 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	word_len(const char *s, char c, int j)
{
	int	i;
	int	count;
	int	n;

	i = 0;
	count = 0;
	n = 0;
	while (n < j - 1)
	{
		while (s[i] == c)
			i++;
		while (s[i] != c)
			i++;
		n++;
	}
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		i++;
		count++;
	}
	return (count);
}

static char	*point_word(int word, const char *s, char sep)
{
	int		i;
	int		count;
	char	*str;

	i = 0;
	str = (char *)s;
	count = 1;
	while (count < word)
	{
		while (str[i] == sep)
			i++;
		while (str[i] != sep)
			i++;
		count++;
	}
	while (str[i] == sep)
		i++;
	return (&str[i]);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		j;

	j = 0;
	res = malloc(sizeof(char *) * (1 + count_words(s, c)));
	if (!res)
		return (NULL);
	while (j < count_words(s, c))
	{
		res[j] = malloc(sizeof(char) * word_len(s, c, j + 1) + 1);
		if (!res[j])
		{
			ft_freeall(res);
			return (NULL);
		}
		ft_strlcpy(res[j], point_word(j + 1, s, c), word_len(s, c, j + 1) + 1);
		j++;
	}
	res[j] = NULL;
	return (res);
}
