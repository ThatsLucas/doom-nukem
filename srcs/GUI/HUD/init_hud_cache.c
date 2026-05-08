/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_cache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:30:07 by edurance          #+#    #+#             */
/*   Updated: 2026/05/08 09:36:42 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "inventory/Items.h"
#include "parser/PNG.h"
#include "Game.h"

/* Processing png on a path (thread_worker) */
static void	*load_png_thread(void *arg)
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

	for (int j = 0; j < 4; j++, i++)
	{
		jobs[i].game = game;
		jobs[i].path = weap_paths[j];
		jobs[i].type = ASSET_WEAPON2D;
		jobs[i].index = j;
	}

	static char *tools_paths[] = {
		"assets/png/hud/tools/flashlight.png",
		"assets/png/hud/tools/key.png",
		"assets/png/hud/tools/jetpack.png",
	};

	for (int j = 0; j < 3; j++, i++)
	{
		jobs[i].game = game;
		jobs[i].path = tools_paths[j];
		jobs[i].type = ASSET_TOOL;
		jobs[i].index = j;
	}

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

	for (int j = 0; j < 10; j++, i++)
	{
		jobs[i].game = game;
		jobs[i].path = player_paths[j];
		jobs[i].type = ASSET_PLAYER;
		jobs[i].index = j;
	}

	return (i);
}

/* Creating threads to process all the assets and join them to create images */
static void	init_all_assets(t_game *game)
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

		if (jobs[i].type == ASSET_WEAPON2D)
		{
			if (!(game->hud_cache.weapon_textures_2D[jobs[i].index] = create_image(&jobs[i].result, game->window->renderPTR)))
				exit_game(game, "create image failed");
		}
		else if (jobs[i].type == ASSET_TOOL)
		{
			if (!(game->hud_cache.tools_textures[jobs[i].index] = create_image(&jobs[i].result, game->window->renderPTR)))
				exit_game(game, "create image failed");
		}
		else if (jobs[i].type == ASSET_PLAYER)
		{
			if (!(game->hud_cache.ply_textures[jobs[i].index] = create_image(&jobs[i].result, game->window->renderPTR)))
				exit_game(game, "create image failed");
		}
	}
}

/* Initialize 3D weapon in multi threads*/
static void	init_3D_weapon(t_game *game, int weapon_idx, char **paths, SDL_Rect *rects, int frame_count, int fire_rate)
{
	t_weapon_3D	*w = &game->hud_cache.weapons_3D[weapon_idx];
	pthread_t	threads[frame_count];
	t_load_job	jobs[frame_count];

	w->fire_rate = fire_rate;
	w->frame_count = frame_count;
	w->current_frame = 0;
	w->is_firing = 0;
	w->last_anim_time = 0;
	w->frames = malloc(sizeof(t_weapon_3D_frame) * frame_count);
	if (!w->frames)
		exit_game(game, "malloc weapon frames");

	for (int i = 0; i < frame_count; i++)
	{
		jobs[i].game = game;
		jobs[i].path = paths[i];
		jobs[i].index = i;

		if (pthread_create(&threads[i], NULL, load_png_thread, &jobs[i]) != 0)
			exit_game(game, "pthread_create_failed");
	}

	for (int i = 0; i < frame_count; i++)
	{
		pthread_join(threads[i], NULL);
		if (!jobs[i].success)
			exit_game(game, "process_png failed");

		w->frames[i].texture = create_image(&jobs[i].result, game->window->renderPTR);
		if (!w->frames[i].texture)
			exit_game(game, "create image weapon 3d");
		w->frames[i].dest = rects[i];
	}
}

/* Initialize 3D weapons */
static void	init_3D_weapons(t_game *game)
{
	static char	*fists_paths[] = {
		"assets/png/hud/weapons/3d/fists/fists_default.png",
		"assets/png/hud/weapons/3d/fists/fists_1.png",
		"assets/png/hud/weapons/3d/fists/fists_2.png",
		"assets/png/hud/weapons/3d/fists/fists_3.png"
	};

	static char	*pistol_paths[] = {
		"assets/png/hud/weapons/3d/pistol/pistol_default.png",
		"assets/png/hud/weapons/3d/pistol/pistol_shoot.png"
	};

	static char	*shotgun_paths[] = {
		"assets/png/hud/weapons/3d/shotgun/shotgun_default.png",
		"assets/png/hud/weapons/3d/shotgun/shotgun_1.png",
		"assets/png/hud/weapons/3d/shotgun/shotgun_2.png",
		"assets/png/hud/weapons/3d/shotgun/shotgun_3.png",
		"assets/png/hud/weapons/3d/shotgun/shotgun_4.png",
	};

	static char	*rocket_paths[] = {
		"assets/png/hud/weapons/3d/rocket/rocket_1.png",
		"assets/png/hud/weapons/3d/rocket/rocket_2.png",
		"assets/png/hud/weapons/3d/rocket/rocket_3.png",
		"assets/png/hud/weapons/3d/rocket/rocket_4.png",
		"assets/png/hud/weapons/3d/rocket/rocket_5.png",
		"assets/png/hud/weapons/3d/rocket/rocket_6.png",
		"assets/png/hud/weapons/3d/rocket/rocket_7.png"
	};

	static SDL_Rect	fists_rects[] = {
		{600, 545, 800, 350},
		{300, 545, 800, 350},
		{300, 545, 800, 350},
		{400, 545, 800, 350}
	};

	static SDL_Rect	pistol_rects[] = {
		{832, 570, 225, 325},
		{830, 570, 225, 325}
	};

	static SDL_Rect	shotgun_rects[] = {
		{755, 640, 330, 250},
		{755, 640, 330, 250},
		{735, 650, 300, 250},
		{735, 650, 300, 250},
		{735, 640, 300, 250}
	};

	static SDL_Rect	rocket_rects[] = {
		{810, 650, 330, 250},
		{810, 650, 330, 250},
		{810, 650, 300, 250},
		{810, 650, 300, 250},
		{810, 650, 300, 250},
		{810, 650, 300, 250},
		{810, 650, 300, 250}
	};

	init_3D_weapon(game, WEAP_FISTS, fists_paths, fists_rects, 4, 90);
	init_3D_weapon(game, WEAP_PISTOL, pistol_paths, pistol_rects, 2, 130);
	init_3D_weapon(game, WEAP_SHOTGUN, shotgun_paths, shotgun_rects, 5, 130);
	init_3D_weapon(game, WEAP_ROCKET_LAUNCHER, rocket_paths, rocket_rects, 7, 100);
}

/*
	Initialize weapons, tools and player assets to keep a cache of textures
	Open and keep fonts in cache
*/
void	init_hud_cache(t_game *game)
{
	//ft_printf("loading hud assets\n");

	init_3D_weapons(game);
	init_all_assets(game);

	t_png	hud_bg;
	hud_bg.path = ft_strdup("assets/png/hud/hudbg.png");
	if (!process_png(&hud_bg))
		exit_game(game, "Error loading hud bg: process failed");
	game->hud_cache.bg_texture = create_image(&hud_bg, game->window->renderPTR);
	if (!game->hud_cache.bg_texture)
		exit_game(game, "Error loading hud bg: create image failed");

	t_png	battery_gauge;
	t_png	battery_unit;
	battery_gauge.path = ft_strdup("assets/png/hud/tools/battery_gauge.png");
	battery_unit.path = ft_strdup("assets/png/hud/tools/battery_unit.png");

	if (!process_png(&battery_gauge) || !process_png(&battery_unit))
		exit_game(game, "Error loading hud battery: process failed");

	game->hud_cache.battery[0] = create_image(&battery_gauge, game->window->renderPTR);
	game->hud_cache.battery[1] = create_image(&battery_unit, game->window->renderPTR);
	if (!game->hud_cache.battery[0] || !game->hud_cache.battery[1])
		exit_game(game, "Error loading hud battery: create image failed");

	t_png	fuel_gauge;
	t_png	fuel_unit;
	fuel_gauge.path = ft_strdup("assets/png/hud/tools/fuel_gauge.png");
	fuel_unit.path = ft_strdup("assets/png/hud/tools/fuel_unit.png");

	if (!process_png(&fuel_gauge) || !process_png(&fuel_unit))
		exit_game(game, "Error loading hud fuel: process failed");

	game->hud_cache.fuel[0] = create_image(&fuel_gauge, game->window->renderPTR);
	game->hud_cache.fuel[1] = create_image(&fuel_unit, game->window->renderPTR);
	if (!game->hud_cache.fuel[0] || !game->hud_cache.fuel[1])
		exit_game(game, "Error loading hud fuel: create image failed");

	game->hud_cache.text_font = TTF_OpenFont("assets/fonts/Jersey25-Regular.ttf", 25);
	game->hud_cache.number_font = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 24);
	game->hud_cache.ply_last_time = get_time_ms();
	game->hud_cache.ply_frame = 0;
	if (!game->hud_cache.text_font || !game->hud_cache.number_font)
		exit_game(game, (char *)TTF_GetError());

	//ft_printf("finished loading hud assets\n");
}
