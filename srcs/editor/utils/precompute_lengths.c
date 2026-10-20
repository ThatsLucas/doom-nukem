/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_lengths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Pré-calcule la longueur de chaque mur. */
void	precompute_lengths(t_map *map)
{
	t_wall	*w;

	for (int i = 0; i < map->num_walls; i++)
	{
		w = &map->walls[i];
		w->length = dist_vect(map->vertices[w->v1], map->vertices[w->v2]);
	}
}
