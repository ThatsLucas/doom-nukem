/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:48:03 by edurance          #+#    #+#             */
/*   Updated: 2026/08/11 14:18:03 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "entities/Entities.h"

/* Vérifie si la position touche la hitbox d’une entité. */
int	entities_collision(t_game *game, float next_x, float next_y)
{
	double	dx, dy, hitbox;

	if (!game->entities.list)
		return (0);

	for (int i = 0; i < game->entities.count; ++i)
	{
		if (game->entities.list[i].hitbox > 0
			&& game->entities.list[i].status != E_STATUS_DEAD)
		{
			dx = next_x - game->entities.list[i].x;
			dy = next_y - game->entities.list[i].y;
			hitbox = game->entities.list[i].hitbox;
			if (dx * dx + dy * dy <= hitbox * hitbox)
				return (1);
		}
	}

	return (0);
}
