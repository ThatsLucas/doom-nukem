/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:21:06 by edurance          #+#    #+#             */
/*   Updated: 2026/04/05 17:23:37 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"

/*
	Calcule le nouvelle angle du joueur
	1073741903 = RIGHT
	1073741904 = LEFT
*/
void	ply_directions(int key, t_ply *ply)
{
	float	old_dir_x;
	float	angle;

	angle = 2.0f;
	old_dir_x = ply->dir_x;
	if (key == 1073741903)
	{
		ply->dir_x = old_dir_x * cosf(angle) - ply->dir_y * sinf(angle);
		ply->dir_y = old_dir_x * sinf(angle) + ply->dir_y * cosf(angle);
	}
	else if (key == 1073741904)
	{
		ply->dir_x = old_dir_x * cosf(angle * -1) - ply->dir_y
			* sinf(angle * -1);
		ply->dir_y = old_dir_x * sinf(angle * -1) + ply->dir_y
			* cosf(angle * -1);
	}
}
