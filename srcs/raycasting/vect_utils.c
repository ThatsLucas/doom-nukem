/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:53:07 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/09 14:54:13 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting.h"

t_vect2	edge(t_vect2 a, t_vect2 b)
{
	t_vect2	res;

	res.x = (b.x - a.x);
	res.y = (b.y - a.y);

	return (res);
}

/*	r × s = r.x * s.y - r.y * s.x	*/
float vect2_product(t_vect2 r, t_vect2 s)
{
	return (r.x * s.y - r.y * s.x);
}

