/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:56:44 by edurance          #+#    #+#             */
/*   Updated: 2025/07/13 18:42:24 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strnstr(const char *big, const char *little, unsigned long len)
{
	unsigned long	i;
	unsigned long	j;
	char			*res;

	i = 0;
	res = (char *)big;
	if (!res[0] && little[0] && len <= 0)
		return (0);
	if ((!res[0] && len <= 0) || !little[0])
		return (res);
	while (res[i] && i < len)
	{
		j = 0;
		if (res[i] == little[j])
		{
			while (res[i + j] == little[j] && (i + j) < len && little[j])
				j++;
		}
		if (little[j] == '\0')
			return (&res[i]);
		i++;
	}
	return (0);
}
