/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane_z.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:03:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/29 11:29:21 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Raycasting/Types.h"

/* retourne la hauteur d'un point x,y sur un plan p */
float	get_plane_z(t_plane p, float x, float y)
{
	if (!p.c)
		return (0.0f);
	return (-(p.a * x + p.b * y + p.d) / p.c);
}
