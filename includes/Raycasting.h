/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:04:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/08 16:39:08 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

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
	int			line_height;
	float		draw_start;
	float		draw_end;
}				t_ray;

t_vect2	edge(t_vect2 a, t_vect2 b);
int		inter_point(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res, float *max);

#endif
