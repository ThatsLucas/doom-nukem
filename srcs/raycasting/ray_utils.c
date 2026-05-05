/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:08:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/21 15:38:56 by lle-duc          ###   ########.fr       */
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
