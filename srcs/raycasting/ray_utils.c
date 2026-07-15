/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:08:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/24 17:17:19 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Raycasting/Types.h"
#include "Game.h"

/* calcule le plan de camera */
t_vect2	get_cam_plane(float FOV, t_vect2 dir)
{
	t_vect2 plane;

	plane.x = -dir.y * FOV;
	plane.y = dir.x * FOV;
	return (plane);
}

/* calcule la dirextion d'un rayon */
t_vect2	get_ray_dir(t_ray *ray, t_ply *ply)
{
	t_vect2	dir;

	dir.x = ply->dir.x + ray->camera_x * ray->plane.x;
	dir.y = ply->dir.y + ray->camera_x * ray->plane.y;

	return (dir);
}

/*
	Un mur de portail est partage par deux secteurs (sector_front et
	sector_back, precalcules au save). Retourne celui des deux qui n'est
	PAS le secteur courant, -1 sinon.
*/
int	wall_other_sector(t_map *map, int wall_idx, int cur_sector)
{
	t_wall	*w;

	w = &map->walls[wall_idx];
	if (w->sector_front == cur_sector)
		return (w->sector_back);
	if (w->sector_back == cur_sector)
		return (w->sector_front);
	return (-1);
}
