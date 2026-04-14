/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:13:27 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/14 13:08:02 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

/*
	Envoie des rayons verticaux de 0 a SCREEN_WIDTH
	Affiche le plafond, le mur et le sol
*/
void	send_rays(t_game *game)
{
	t_ray		ray;
	int			sW = game->screenSize[0], sH = game->screenSize[1];

	ray.plane = get_cam_plane(game->ply->dir);

	for (int x = 0; x < sW; x++)
	{
		ray.y_top = 0;
		ray.y_bot = sH - 1;
		ray.camera_x	= 2.0f * x / (float)sW - 1.0f;
		ray.dir			= get_ray_dir(&ray, game->ply);
		ray.focal		= sW / (2.0f * FOV);
		draw_col(game, &ray, x, game->ply->sector, -1);
	}

	return ;
}
