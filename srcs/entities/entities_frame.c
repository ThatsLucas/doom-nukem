/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_frame.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:40:04 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 16:28:23 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"
#include <math.h>

/* Choisit l’image directionnelle selon l’angle entité-joueur. */
int	get_directional_frame(t_entity *e, float px, float py)
{
	int	n = e->num_frames;

	float	to_px = e->x - px;
	float	to_py = e->y - py;

	float	e_angle = atan2f(e->dir_y, e->dir_x);
	float	view_angle = atan2f(to_py, to_px);

	float	rel = e_angle - view_angle;

	// normaliser l'angle pour qu'il soit etre PI et -PI
	while (rel > M_PI)
		rel -= 2.0f * M_PI;
	while (rel < -M_PI)
		rel += 2.0f * M_PI;

	// normaliser l'angle pour que ca donne un indexe de frame
	float	normalized = (rel + M_PI) / (2.0f * M_PI);
	int		frame = (int)(normalized * n) % n;

	if (frame < 0)
		frame += n;
	return (frame);
}
