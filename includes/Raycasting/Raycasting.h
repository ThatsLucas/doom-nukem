/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:04:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/11 11:12:51 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

#include "../libft/include/libft.h"
#include "Raycasting/Types.h"

typedef struct s_game	t_game;

/*utils vect*/
t_vect2	edge(t_vect2 a, t_vect2 b);
float	vect2_product(t_vect2 r, t_vect2 s);
float	dist_vect(t_vect2 a, t_vect2 b);

/*Raycasting*/
float	inter_point(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res);
float	inter_point_filter(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res);
int		max_inter_point(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res, float *max);
int		wall_side(t_wall *splitter, t_wall *wall);

/*BSP*/
t_list	*best_splitter(t_list **first);
t_bsp	*bsp(t_game *game, t_list *walls);
void	free_bsp(t_bsp *node);
void	get_smaller_ray(t_game *game, t_bsp *node, t_ray *ray, float *t);

#endif
