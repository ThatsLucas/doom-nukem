/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_weapons.c                                 :+:      :+:    :+:   */
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

/* Initialise l’arme 3D et ses animations. */
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

/* Initialise les sprites 3D des poings. */
static void	init_3D_fists(t_game *game)
{
	static char	*fists_paths[] = {
		"assets/png/hud/weapons/3d/fists/fists_default.png",
		"assets/png/hud/weapons/3d/fists/fists_1.png",
		"assets/png/hud/weapons/3d/fists/fists_2.png",
		"assets/png/hud/weapons/3d/fists/fists_3.png"
	};

	static SDL_Rect	fists_rects[] = {
		{600, 545, 800, 350},
		{300, 545, 800, 350},
		{300, 545, 800, 350},
		{400, 545, 800, 350}
	};

	init_3D_weapon(game, WEAP_FISTS, fists_paths, fists_rects, 4, 90);
}

/* Initialise les sprites 3D du pistolet. */
static void	init_3D_pistol(t_game *game)
{
	static char	*pistol_paths[] = {
		"assets/png/hud/weapons/3d/pistol/pistol_default.png",
		"assets/png/hud/weapons/3d/pistol/pistol_shoot.png"
	};

	static SDL_Rect	pistol_rects[] = {
		{832, 570, 225, 325},
		{830, 570, 225, 325}
	};

	init_3D_weapon(game, WEAP_PISTOL, pistol_paths, pistol_rects, 2, 130);
}

/* Initialise les sprites 3D du fusil à pompe. */
static void	init_3D_shotgun(t_game *game)
{
	static char	*shotgun_paths[] = {
		"assets/png/hud/weapons/3d/shotgun/shotgun_default.png",
		"assets/png/hud/weapons/3d/shotgun/shotgun_1.png",
		"assets/png/hud/weapons/3d/shotgun/shotgun_2.png",
		"assets/png/hud/weapons/3d/shotgun/shotgun_3.png",
		"assets/png/hud/weapons/3d/shotgun/shotgun_4.png",
	};

	static SDL_Rect	shotgun_rects[] = {
		{755, 640, 330, 250},
		{755, 640, 330, 250},
		{735, 650, 300, 250},
		{735, 650, 300, 250},
		{735, 640, 300, 250}
	};

	init_3D_weapon(game, WEAP_SHOTGUN, shotgun_paths, shotgun_rects, 5, 130);
}

/* Initialise les sprites 3D du lance-roquettes. */
static void	init_3D_rocket(t_game *game)
{
	static char	*rocket_paths[] = {
		"assets/png/hud/weapons/3d/rocket/rocket_1.png",
		"assets/png/hud/weapons/3d/rocket/rocket_2.png",
		"assets/png/hud/weapons/3d/rocket/rocket_3.png",
		"assets/png/hud/weapons/3d/rocket/rocket_4.png",
		"assets/png/hud/weapons/3d/rocket/rocket_5.png",
		"assets/png/hud/weapons/3d/rocket/rocket_6.png",
		"assets/png/hud/weapons/3d/rocket/rocket_7.png"
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

	init_3D_weapon(game, WEAP_ROCKET_LAUNCHER, rocket_paths, rocket_rects, 7, 100);
}

/* Initialise les sprites 3D de toutes les armes. */
void	init_3D_weapons(t_game *game)
{
	init_3D_fists(game);
	init_3D_pistol(game);
	init_3D_shotgun(game);
	init_3D_rocket(game);
}
