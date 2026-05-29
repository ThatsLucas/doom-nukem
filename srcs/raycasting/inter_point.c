/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:09:15 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/25 14:48:24 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"

/*
	Calcule le point d'intersection entre deux vecteurs ou:
	- P est le point de depart
	- r est la direction de depart
	- Q est le point de depart de l'edge (vecteur rencontre)
	- s est la direction de l'edge

	r*s doit etre different de 0 pour que les deux vecteurs se croisent
	t doit etre superieur ou egal a 0 (sinon l'intersection est derriere le vecteur P)
	u doit etre entre 0 et 1 sinon l'intersection est en dehors de l'edge

	Remplis les donnes de ray avec le point de l'intersection
	Sinon une donnee est invalide ( pas d'intersection utile )
*/
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

