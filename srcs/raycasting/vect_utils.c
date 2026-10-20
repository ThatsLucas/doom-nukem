/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:53:07 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/16 17:54:57 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

/* Renvoie le vecteur allant de a à b. */
t_vect2	edge(t_vect2 a, t_vect2 b)
{
	t_vect2	res;

	res.x = (b.x - a.x);
	res.y = (b.y - a.y);

	return (res);
}

/* Calcule le produit vectoriel 2D. */
float vect2_product(t_vect2 r, t_vect2 s)
{
	return (r.x * s.y - r.y * s.x);
}

/* Calcule la distance entre deux points. */
float	dist_vect(t_vect2 a, t_vect2 b)
{
	float	len;

	len = sqrtf(powf(b.x - a.x, 2.0f) + (powf(b.y - a.y, 2.0f)));

	return (len);
}
