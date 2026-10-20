/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:13:27 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:31:47 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

/* Calcule les rayons affectés aux fils d’exécution. */
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

	float camera_scale = tanf(game->settings.FOV * 0.5f);

	ray.plane = get_cam_plane(camera_scale, game->ply->dir);
	ray.focal = sW / (2.0f * camera_scale);
	ray.inv_focal = 1.0f / ray.focal;

	for (int x = infos->x_start; x < infos->x_end; x++)
	{
		ray.perp_dist = FLT_MAX;
		ray.wall_idx = -1;
		ray.y_top = 0;
		ray.y_bot = sH - 1;
		ray.camera_x = 2.0f * x / (float)sW - 1.0f;
		ray.screen_x = x;
		ray.dir = get_ray_dir(&ray, game->ply);
		for (int y = 0; y < sH; y++)
			game->z_buffer[y * sW + x] = FLT_MAX;
		draw_col(game, &ray, x, game->ply->sector, -1);
		game->rays[x] = ray;
	}

	pthread_exit(NULL);
	return (NULL);
}

/* Lance un rayon par colonne de l’écran pour dessiner la scène. */
void send_rays(t_game *game)
{
	t_raythread infos[RAYCAST_THREADS];
	pthread_t threads[RAYCAST_THREADS];
	int parts, start;

	parts = game->screenSize[0] / RAYCAST_THREADS;
	start = 0;
	for (int i = 0; i < RAYCAST_THREADS; i++)
	{
		infos[i].game = game;
		infos[i].x_start = start;
		infos[i].x_end = start + parts;
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
	return ;
}
