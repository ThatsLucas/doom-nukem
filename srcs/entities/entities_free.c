/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:37:02 by edurance          #+#    #+#             */
/*   Updated: 2026/04/17 14:38:53 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"

void	free_entities(t_entities *e)
{
	if (e->list)
		free(e->list);

	e->list = NULL;
	e->count = 0;
	e->capacity = 0;
}
