/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_smaller_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 11:31:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/13 22:22:14 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

// static void select_smaller(t_vect2 inter, float *t, float *tab, t_ray *ray, t_ray *ray_tab, t_wall splt)
// {
// 	*t   = (*t   < 0 ? FLT_MAX : *t);
// 	tab[0] = (tab[0] < 0 ? FLT_MAX : tab[0]);
// 	tab[1] = (tab[1] < 0 ? FLT_MAX : tab[1]);
// 	if (*t < tab[0] && *t < tab[1])
// 	{
// 		ray->splitter		= splt;
// 		ray->intersection	= inter;
// 		return ;
// 	}
// 	if (tab[0] < tab[1] && tab[0] < *t)
// 	{
// 		*t					= tab[0];
// 		ray->splitter		= ray_tab[0].splitter;
// 		ray->intersection	= ray_tab[0].intersection;
// 		return ;
// 	}
// 	*t						= tab[1];
// 	ray->splitter			= ray_tab[1].splitter;
// 	ray->intersection		= ray_tab[1].intersection;

// 	return ;
// }


// void	get_smaller_ray(t_game *game, t_bsp *node, t_ray *ray, float *t)
// {
// 	int		side;
// 	t_vect2	tab[3];
// 	float	t_tab[2];
// 	t_ray	ray_tab[2];
	
// 	ray_tab[0] = *ray;			ray_tab[1] = *ray;
// 	t_tab[0] = FLT_MAX;			t_tab[1] = FLT_MAX;
// 	ray->intersection.x = -1;	ray->intersection.y = -1;
// 	if (!node)
// 		return ;
// 	ray->splitter = node->splitter;
// 	*t = inter_point_filter(game->ply->pos, ray->ray_dir, node->splitter.start, edge(node->splitter.start, node->splitter.end), &tab[0]);

// 	side = vect2_product(edge(node->splitter.start, node->splitter.end), edge(node->splitter.start, game->ply->pos));
// 	if (side >= 0)
// 	{
// 		get_smaller_ray(game, node->front, &ray_tab[0], &t_tab[0]);
// 		get_smaller_ray(game, node->back, &ray_tab[1], &t_tab[1]);
// 	}
// 	else
// 	{
// 		get_smaller_ray(game, node->back, &ray_tab[0], &t_tab[0]); 
// 		get_smaller_ray(game, node->front, &ray_tab[1], &t_tab[1]);
// 	}

// 	select_smaller(tab[0], t, t_tab, ray, ray_tab, node->splitter);

// 	return ;
// }
