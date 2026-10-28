/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 01:39:06 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:21:13 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

/* Déclenche le mouvement de l’ascenseur. */
void	toggle_elevator(t_sector *s)
{
	if (s->isElevating)
		return ;

	s->levelRemaining = (float)s->levelSize;
	s->lastMove = get_timestamp();
	s->isElevating = 1;

	return ;
}

/* Fait avancer les ascenseurs en mouvement. */
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
			s->trips++;
		}
	}
}

/* Renvoie 1 si le joueur est dans un ascenseur de sortie arrivé en bas. */
int	is_on_level_exit(t_game *game)
{
	t_sector	*s;
	int			id;

	id = game->ply->sector;
	if (id < 0 || id >= game->map->num_sectors)
		return (0);
	s = &game->map->sectors[id];
	/* premier trajet terminé et c'était une descente (direction repassée à 1) */
	if (s->isElevating || s->trips != 1 || s->levelSize <= 0 || s->direction != 1)
		return (0);
	/* un ascenseur de sortie s'actionne depuis l'intérieur, contrairement aux portes */
	for (int i = 0; i < game->map->num_decals; ++i)
	{
		if (game->map->decals[i].elev_sector == id
			&& game->map->decals[i].sector_id == id)
			return (1);
	}
	return (0);
}
