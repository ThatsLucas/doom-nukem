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

/* Vide la liste des entités (leurs textures restent dans le cache). */
void	clear_entities(t_entities *e)
{
	for (int i = 0; i < e->count; i++)
	{
		free(e->list[i].textures);
		e->list[i].textures = NULL;
	}
	e->count = 0;
}

/* Libère toutes les entités. */
void	free_entities(t_entities *e)
{
	if (e->list)
	{
		clear_entities(e);
		free(e->list);
	}

	e->list = NULL;
	e->count = 0;
	e->capacity = 0;
}
