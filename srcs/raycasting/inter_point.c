/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:09:15 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/14 13:02:46 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"

/* Met à jour le rayon si son intersection avec le mur est valide. */
void	max_inter_point(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_ray *ray, int wall_idx)
{
	t_vect2	qp;
	float	rs, t, u;

	rs = vect2_product(r, s);
	qp = edge(P, Q);

	if (rs == 0)
		return ;
	t = vect2_product(qp, s) / rs;
	if (t < 0)
		return ;
	u = vect2_product(qp, r) / rs;
	if (u < 0 || u > 1)
		return ;

	if (t < ray->t)
	{
		ray->t			= t;
		ray->u			= u;
		ray->hit.x		= P.x + t * r.x;
		ray->hit.y		= P.y + t * r.y;
		ray->wall_idx	= wall_idx;
	}
	return ;
}

/* Calcule l’intersection de deux droites et renvoie t. */
float	inter_point(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res)
{
	t_vect2	qp;
	float	rs, t;

	rs = vect2_product(r, s);
	qp = edge(P, Q);

	if (rs == 0)
		return (-1);
	t = vect2_product(qp, s) / rs;

	(*res).x = P.x + t * r.x;
	(*res).y = P.y + t * r.y;
	return (t);
}

/* Calcule l’intersection d’un rayon et d’un segment, -1 si aucune. */
float	inter_point_filter(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res)
{
	t_vect2	qp;
	float	rs, t, u;

	rs = vect2_product(r, s);
	qp = edge(P, Q);

	if (rs == 0)
		return (-1);
	t = vect2_product(qp, s) / rs;
	if (t < 0)
		return (-1);
	u = vect2_product(qp, r) / rs;
	if (u < 0 || u > 1)
		return (-1);

	(*res).x = P.x + t * r.x;
	(*res).y = P.y + t * r.y;
	return (t);
}

