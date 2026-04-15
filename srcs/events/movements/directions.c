/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:21:06 by edurance          #+#    #+#             */
/*   Updated: 2026/04/15 12:59:43 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"

/*
	Calcule le nouvelle angle du joueur
	1073741903 = RIGHT
	1073741904 = LEFT
*/
void	ply_directions(t_ply *ply)
{
	float	old_dir_x;
	float	angle;

	angle = 0.03f;
	old_dir_x = ply->dir.x;
	if (ply->keys.right && ply->keys.left)
		return ;
	else if (ply->keys.right)
	{
		ply->dir.x = old_dir_x * cosf(angle) - ply->dir.y * sinf(angle);
		ply->dir.y = old_dir_x * sinf(angle) + ply->dir.y * cosf(angle);
	}
	else if (ply->keys.left)
	{
		ply->dir.x = old_dir_x * cosf(angle * -1) - ply->dir.y
			* sinf(angle * -1);
		ply->dir.y = old_dir_x * sinf(angle * -1) + ply->dir.y
			* cosf(angle * -1);
	}

	return ;
}
