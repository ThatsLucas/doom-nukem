/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_on_segment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:44:55 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/04 16:34:09 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Vérifie si un point se trouve sur un segment. */
int point_on_segment(t_vect2 a, t_vect2 b, t_vect2 c, float eps)
{
	t_vect2	bc = edge(b, c);
	t_vect2	ba = edge(b, a);
	float	cross = vect2_product(bc, ba);
	float	len = sqrtf(bc.x * bc.x + bc.y * bc.y);
	float	dot;

	if (len < 1e-6f)
		return (0);
	if (fabsf(cross) / len > eps)
		return (0);
	dot = ba.x * bc.x + ba.y * bc.y;
	return (dot >= 0.0f && dot <= len * len);
}
