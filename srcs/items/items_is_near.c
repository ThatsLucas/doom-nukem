/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_is_near.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:11:32 by edurance          #+#    #+#             */
/*   Updated: 2026/04/08 17:11:34 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Vérifie si le joueur est assez près pour ramasser l’objet. */
int	is_near(float px, float py, float ix, float iy, float range)
{
	float	dx, dy;
	float	dist_squared, range_squared;

	dx = px -ix;
	dy = py - iy;

	dist_squared = (dx * dx) + (dy * dy);
	range_squared = range * range;

	return (dist_squared <= range_squared);
}
