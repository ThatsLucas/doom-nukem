/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:34:27 by edurance          #+#    #+#             */
/*   Updated: 2026/04/17 14:36:39 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"

/* Ajoute une entité à la liste. */
void	add_entity(t_game *game, t_entities *e, t_entity entity)
{
	if (e->count >= e->capacity)
	{
		e->capacity = (e->capacity > 0) ? e->capacity * 2 : 16;
		e->list = realloc(e->list, sizeof(t_entity) * e->capacity);
		if (!e->list)
			exit_game(game, "realloc entity failed");
	}

	e->list[e->count++] = entity;
}
