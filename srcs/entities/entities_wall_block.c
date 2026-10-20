/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_wall_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:40:04 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 11:40:04 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"

static float	distance(t_vect2 a, t_vect2 b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

/*
	Renvoie 1 si un mur plein du secteur coupe le segment entite -> joueur
	avant d'atteindre le joueur.
*/
static int	sector_blocks_ray(t_game *game, int sector_id, t_vect2 e_pos, t_vect2 p_pos)
{
	t_sector	*sector = &game->map->sectors[sector_id];
	t_wall		*wall;
	t_vect2		ray_dir = {p_pos.x - e_pos.x, p_pos.y - e_pos.y};
	t_vect2		hit_point;

	for (int i = 0; i < sector->num_walls; i++)
	{
		wall = &game->map->walls[sector->walls[i]];

		/* saute les murs transparents ou portals */
		if (wall->next_sector != -1)
			continue ;

		t_vect2 wall_v1 = game->map->vertices[wall->v1];
		t_vect2 wall_v2 = game->map->vertices[wall->v2];
		t_vect2 wall_edge = edge(wall_v1, wall_v2);

		/* intersection avec le rayon et le mur */
		float t = inter_point(e_pos, ray_dir, wall_v1, wall_edge, &hit_point);

		/* si le mur est plus proche que le joueur */
		if (t > 0.001f && t < 1.0f
			&& distance(e_pos, hit_point) < distance(e_pos, p_pos) - 0.01f)
			return (1);
	}
	return (0);
}

/* Renvoie 0 si un mur bloque la vue entre l'entite et le joueur */
int	check_wall_blocking(t_game *game, float ex, float ey, int entity_sector, float px, float py)
{
	t_vect2		e_pos = {ex, ey};
	t_vect2		p_pos = {px, py};
	t_vect2		ray_dir = {px - ex, py - ey};
	float		ray_length;

	ray_length = sqrt(ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y);
	if (ray_length < 0.001f)
		return (1);

	/* mur du secteur de l'entite */
	if (entity_sector >= 0 && entity_sector < game->map->num_sectors
		&& sector_blocks_ray(game, entity_sector, e_pos, p_pos))
		return (0);

	/* murs du secteur du joueur */
	if (sector_blocks_ray(game, game->ply->sector, e_pos, p_pos))
		return (0);
	return (1);
}
