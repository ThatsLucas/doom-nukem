/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_editor_plan.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 11:58:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/29 22:55:42 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Efface toute la carte de l’éditeur. */
void	clear_editor_plan(t_game *game)
{
	t_map	*map = game->editor->map;

	map->num_sectors = 0;
	map->num_vertices = 0;
	map->num_walls = 0;

	return ;
}
