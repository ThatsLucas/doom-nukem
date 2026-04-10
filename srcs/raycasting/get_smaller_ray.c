/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_smaller_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 11:31:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/10 11:32:04 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting.h"
#include "Game.h"

static t_vect2	select_smaller(t_vect2	*tab, float *t, float *t_b, float *t_c)
{
	*t = (*t < 0 ? FLT_MAX : *t);
	*t_b = (*t_b < 0 ? FLT_MAX : *t_b);
	*t_c = (*t_c < 0 ? FLT_MAX : *t_c);

	if (*t < *t_b && *t < *t_c)
		return (tab[0]);
	if (*t_b < *t_c && *t_b < *t)
	{
		*t = *t_b;
		return (tab[1]);
	}
	*t = *t_c;
	return (tab[2]);
}

t_vect2	get_smaller_ray(t_game *game, t_bsp *node, t_ray *ray, float *t)
{
	int		side;
	t_wall	splitr;
	t_vect2	tab[3];
	float	t_b = FLT_MAX, t_c = FLT_MAX;

	tab[0].x = -1.0f;
	tab[0].y = -1.0f;
	if (!node)
		return (tab[0]);
	splitr = node->splitter;
	*t = inter_point_filter(game->ply->pos, ray->ray_dir, splitr.start, edge(splitr.start, splitr.end), &tab[0]);

	side = vect2_product(edge(splitr.start, splitr.end), edge(splitr.start, game->ply->pos));
	if (side >= 0)
	{
		tab[1] = get_smaller_ray(game, node->front, ray, &t_b);
		tab[2] = get_smaller_ray(game, node->back, ray, &t_c);
	}
	else
	{
		tab[1] = get_smaller_ray(game, node->back, ray, &t_b);
		tab[2] = get_smaller_ray(game, node->front, ray, &t_c);
	}

	return (select_smaller(tab, t, &t_b, &t_c));
}
