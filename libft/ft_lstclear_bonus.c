/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:27:52 by edurance          #+#    #+#             */
/*   Updated: 2025/11/03 15:51:49 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*first;
	t_list	*temp;

	if (!lst)
		return ;
	first = *lst;
	while (first)
	{
		temp = first;
		first = first->next;
		ft_lstdelone(temp, del);
	}
	*lst = NULL;
}
