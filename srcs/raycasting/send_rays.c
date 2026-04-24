/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:13:27 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/21 15:39:11 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

static void *send_threads_ray(void *arg)
{
	t_raythread *infos;
	t_game *game;
	t_ray ray;
	int sW, sH;

	infos = (t_raythread *)arg;
	game = infos->game;
	sW = game->screenSize[0];
	sH = game->screenSize[1];

	ray.plane = get_cam_plane(infos->camera_scale, game->ply->dir);
	ray.focal = sW / (2.0f * infos->camera_scale);
	ray.inv_focal = 1.0f / ray.focal;

	for (int x = infos->x_start; x < infos->x_end; x++)
	{
		ray.y_top = 0;
		ray.y_bot = sH - 1;
		ray.camera_x = 2.0f * x / (float)sW - 1.0f;
		ray.dir = get_ray_dir(&ray, game->ply);
		draw_col(game, &ray, x, game->ply->sector, -1);
	}

	pthread_exit(NULL);
	return (NULL);
}

/*
	Envoie des rayons verticaux de 0 a SCREEN_WIDTH
	Affiche le plafond, le mur et le sol
*/
void send_rays(t_game *game)
{
	t_raythread infos[RAYCAST_THREADS];
	pthread_t threads[RAYCAST_THREADS];
	int parts, start;

	float camera_scale = tanf(game->settings.FOV * 0.5f);
	parts = game->screenSize[0] / RAYCAST_THREADS;
	start = 0;

	for (int i = 0; i < RAYCAST_THREADS; i++)
	{
		infos[i].game = game;
		infos[i].x_start = start;
		infos[i].x_end = start + parts;
		infos[i].camera_scale = camera_scale;
		if (i == RAYCAST_THREADS - 1)
			infos[i].x_end = game->screenSize[0];
		start += parts;

		if (pthread_create(&threads[i], NULL, send_threads_ray, &infos[i]))
		{
			for (int x = 0; x < i; x++)
				pthread_join(threads[x], NULL);
			exit_game(game, "send_rays threads");
		}
	}

	for (int y = 0; y < RAYCAST_THREADS; y++)
		pthread_join(threads[y], NULL);
	return;
}
