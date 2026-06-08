/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:32:59 by edurance          #+#    #+#             */
/*   Updated: 2026/05/04 15:57:36 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"

void	init_entities(t_entities *e)
{
	e->count = 0;
	e->capacity = 16;
	e->list = malloc(sizeof(t_entity) * e->capacity);
}
