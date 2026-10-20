/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:16:51 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:16:51 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "inventory/Items.h"
#include "parser/PNG.h"
#include "Game.h"

/* Processing png on a path (thread_worker) */
void	*load_png_thread(void *arg)
{
	t_load_job	*job = (t_load_job *)arg;

	job->success = 1;
	job->result.path = ft_strdup(job->path);
	if (!process_png(&job->result))
	{
		job->success = 0;
		ft_printf("Error loading %s\n", job->path);
	}

	return (NULL);
}

/* Adds count jobs of the same type, returns the next free index */
static int	add_jobs(t_game *game, t_load_job *jobs, int i, char **paths, int count, int type)
{
	for (int j = 0; j < count; j++, i++)
	{
		jobs[i].game = game;
		jobs[i].path = paths[j];
		jobs[i].type = type;
		jobs[i].index = j;
	}
	return (i);
}

/* Fill jobs with the good paths, index and types */
static int	fill_jobs(t_game *game, t_load_job *jobs)
{
	int i = 0;

	static char *weap_paths[] = {
		"assets/png/hud/weapons/2d/fist.png",
		"assets/png/hud/weapons/2d/pistol.png",
		"assets/png/hud/weapons/2d/shotgun.png",
		"assets/png/hud/weapons/2d/rocket.png",
	};

	static char *tools_paths[] = {
		"assets/png/hud/tools/flashlight.png",
		"assets/png/hud/tools/key.png",
		"assets/png/hud/tools/jetpack.png",
	};

	static char *player_paths[] = {
		"assets/png/hud/player/default/default_1.png",
		"assets/png/hud/player/default/default_2.png",
		"assets/png/hud/player/default/default_3.png",

		"assets/png/hud/player/injured/injured_1.png",
		"assets/png/hud/player/injured/injured_2.png",
		"assets/png/hud/player/injured/injured_3.png",

		"assets/png/hud/player/bleeding/bleeding_1.png",
		"assets/png/hud/player/bleeding/bleeding_2.png",
		"assets/png/hud/player/bleeding/bleeding_3.png",

		"assets/png/hud/player/dead/dead_1.png",
	};

	i = add_jobs(game, jobs, i, weap_paths, 4, ASSET_WEAPON2D);
	i = add_jobs(game, jobs, i, tools_paths, 3, ASSET_TOOL);
	i = add_jobs(game, jobs, i, player_paths, 10, ASSET_PLAYER);
	return (i);
}

/* Creates the texture of a finished job and stores it in the hud cache */
static void	store_job_texture(t_game *game, t_load_job *job)
{
	SDL_Texture	**dst = NULL;

	if (job->type == ASSET_WEAPON2D)
		dst = &game->hud_cache.weapon_textures_2D[job->index];
	else if (job->type == ASSET_TOOL)
		dst = &game->hud_cache.tools_textures[job->index];
	else if (job->type == ASSET_PLAYER)
		dst = &game->hud_cache.ply_textures[job->index];
	if (!dst)
		return ;
	if (!(*dst = create_image(&job->result, game->window->renderPTR)))
		exit_game(game, "create image failed");
}

/* Creating threads to process all the assets and join them to create images */
void	init_all_assets(t_game *game)
{
	pthread_t	threads[64]; // valeur par defaut pour avoir une taille
	t_load_job	jobs[64];

	int count = fill_jobs(game, jobs);

	for (int i = 0; i < count; i++)
	{
		if (pthread_create(&threads[i], NULL, load_png_thread, &jobs[i]) != 0)
			exit_game(game, "pthread_create failed");
	}

	for (int i = 0; i < count; i++)
	{
		pthread_join(threads[i], NULL);

		if (!jobs[i].success)
			exit_game(game, "process_png failed");
		store_job_texture(game, &jobs[i]);
	}
}
