/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:04:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/16 23:38:03 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

#include "../libft/include/libft.h"
#include "Raycasting/Types.h"

typedef struct s_game	t_game;
typedef struct s_ply	t_ply;

/*utils vect*/
t_vect2	edge(t_vect2 a, t_vect2 b);
float	vect2_product(t_vect2 r, t_vect2 s);
float	dist_vect(t_vect2 a, t_vect2 b);

/*Raycasting*/
float	inter_point(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res);
float	inter_point_filter(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res);
void	max_inter_point(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_ray *ray, int wall_idx);
float	get_plane_z(t_plane p, float x, float y);
t_vect2	get_cam_plane(t_vect2 dir);
t_vect2	get_ray_dir(t_ray *ray, t_ply *ply);
void	blend_pixels(t_game *game, t_wall *w, t_ray *ray, int x, t_sector *sector);

/* envoie de rayon */
void	send_rays(t_game *game);
void	find_smaller_ray(t_game *game, t_sector *sector, t_ray *ray, int skip_wall);
int		find_mirror_wall(t_map *map, int wall_idx, int next_sector_id);
void	draw_col(t_game *game, t_ray *ray, int x, int sector_id, int skip_wall);

void	update_player_sector(t_game *game, t_vect2 oldpos);

#endif
