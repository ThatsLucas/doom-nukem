/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:37:07 by edurance          #+#    #+#             */
/*   Updated: 2025/07/13 18:39:32 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *pomme)
{
	t_list	*boite;

	boite = malloc(sizeof(t_list));
	if (!boite)
		return (NULL);
	boite->content = pomme;
	boite->next = NULL;
	boite->previous = NULL;
	return (boite);
}
