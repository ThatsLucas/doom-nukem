/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:18:06 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/11 11:14:38 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct	s_vect2
{
	float	x;
	float	y;
}			t_vect2;

typedef struct s_wall
{
	t_vect2	start;
	t_vect2	end;
	int		textureID;
	float	transparency;
}			t_wall;

typedef struct	s_bsp
{
	t_wall			splitter;
	struct s_bsp	*front;
	struct s_bsp	*back;
}					t_bsp;

typedef struct s_ray
{
	t_vect2		ray_dir;
	t_vect2		plane;
	float		camera_x;
	int			draw_start;
	int			draw_end;
	int			height;
	int			screen_x;
	float		wall_x;
	float		text_y;
	t_wall		splitter;
	t_vect2		intersection;

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
	int			side;
	int			text_x;
}				t_ray;

#endif
