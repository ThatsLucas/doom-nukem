/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 01:39:06 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/29 16:13:12 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

void	toggle_elevator(t_sector *s)
{
	printf("==> toggle\n");
	if (s->isElevating)
		return ;

	printf("==> done\n");
	s->levelRemaining = (float)s->levelSize;
	s->lastMove = get_timestamp();
	s->isElevating = 1;

	return ;
}

void	check_elevator(t_map *map)
{
	t_sector	*s;
	long		now;
	float		move;

	now = get_timestamp();
	for (int i = 0; i < map->num_sectors; ++i)
	{
		s = &map->sectors[i];
		if (!s->isElevating)
			continue ;

		move = ELEVATOR_SPEED * (now - s->lastMove) / 1000.0f;
		s->lastMove = now;
		if (move > s->levelRemaining)
			move = s->levelRemaining;
		s->floor_plane.d += (s->direction) ? -move : move;
		s->ceil_plane.d += (s->direction) ? -move : move;
		s->levelRemaining -= move;
		if (s->levelRemaining <= 0.0f)
		{
			s->direction = s->direction ? 0 : 1;
			s->isElevating = 0;
		}
	}
}
