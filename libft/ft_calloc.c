/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:06:45 by edurance          #+#    #+#             */
/*   Updated: 2025/07/13 18:37:56 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(unsigned long nmemb, unsigned long size)
{
	void			*res;
	unsigned long	totalbytes;

	totalbytes = nmemb * size;
	if (totalbytes > 2147483647)
		return (NULL);
	res = malloc(totalbytes);
	if (!res)
		return (NULL);
	ft_bzero(res, totalbytes);
	return (res);
}
