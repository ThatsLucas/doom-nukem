/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:04:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/10 11:38:13 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

#include "../libft/include/libft.h"

typedef struct s_game	t_game;
typedef struct s_RGB	t_RGB;
typedef struct s_wall	t_wall;
typedef struct s_bsp	t_bsp;

typedef struct	s_vect2
{
	float	x;
	float	y;
}			t_vect2;

typedef struct s_ray
{
	t_vect2		ray_dir;
	t_vect2		plane;
	float		camera_x;
	int			draw_start;
	int			draw_end;
	int			height;
	int			screen_x;

	/*not used yet*/
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	float		sidedist_x;
	float		sidedist_y;
	float		deltadist_x;
	float		deltadist_y;
	float		perp_wall_dist;
	float		wall_x;
	int			side;
	int			text_x;
}				t_ray;

/*utils vect*/
t_vect2	edge(t_vect2 a, t_vect2 b);
float	vect2_product(t_vect2 r, t_vect2 s);

/*Raycasting*/
float	inter_point(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res);
float	inter_point_filter(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res);
int		max_inter_point(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res, float *max);
int		wall_side(t_wall *splitter, t_wall *wall);

/*BSP*/
t_list	*best_splitter(t_list **first);
t_bsp	*bsp(t_game *game, t_list *walls);
void	free_bsp(t_bsp *node);
t_vect2	get_smaller_ray(t_game *game, t_bsp *node, t_ray *ray, float *t);

#endif
