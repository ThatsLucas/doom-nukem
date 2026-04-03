/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:51:23 by edurance          #+#    #+#             */
/*   Updated: 2025/08/10 17:00:55 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*gets the element i want given the position in the list*/
t_list	*ft_lstget(t_list *stack, int place)
{
	int	i;

	i = 0;
	while (stack && i < place)
	{
		stack = stack->next;
		i++;
	}
	return (stack);
}
