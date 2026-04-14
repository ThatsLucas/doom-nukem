/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_cache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:30:07 by edurance          #+#    #+#             */
/*   Updated: 2026/04/14 11:53:47 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "inventory/Items.h"
#include "parser/PNG.h"
#include "Game.h"

/* Initialize weapons assets cache in hud_cache.weapon_textures */
static void	init_weapons_cache(t_game *game)
{
	static char	*weap_paths[MAX_WEAPONS] = {
		"assets/png/hud/weapons/2d/fist.png",
		"assets/png/hud/weapons/2d/pistol.png",
		"assets/png/hud/weapons/2d/shotgun.png",
		"assets/png/hud/weapons/2d/rocket.png",
	};

	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		t_png	tmp;
		tmp.path = ft_strdup(weap_paths[i]);
		if (!process_png(&tmp))
			exit_game(game, "process png");
		game->hud_cache.weapon_textures_2D[i] = create_image(&tmp, game->window->renderPTR);
		if (!game->hud_cache.weapon_textures_2D[i])
			exit_game(game, "game_HUD_cache");
	}
}

/* Initialize tools assets cache in hud_cache.tools_textures */
static void	init_tools_cache(t_game *game)
{
	static char	*tools_paths[MAX_TOOLS] = {
		"assets/png/hud/tools/flashlight.png",
		"assets/png/hud/tools/key.png",
		"assets/png/hud/tools/jetpack.png",
	};

	for (int i = 0; i < MAX_TOOLS; i++)
	{
		t_png	tmp;
		tmp.path = ft_strdup(tools_paths[i]);
		if (!process_png(&tmp))
			exit_game(game, "process png");
		game->hud_cache.tools_textures[i] = create_image(&tmp, game->window->renderPTR);
		if (!game->hud_cache.tools_textures[i])
			exit_game(game, "game_HUD_cache");
	}
}

/* Initialize player assets cache in hud_cache.player_textures */
static void	init_player_cache(t_game *game)
{
	static char	*player_paths[10] = {
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

	for (int i = 0; i < 10; i++)
	{
		t_png	tmp;
		tmp.path = ft_strdup(player_paths[i]);
		if (!process_png(&tmp))
			exit_game(game, "process png");
		game->hud_cache.ply_textures[i] = create_image(&tmp, game->window->renderPTR);
		if (!game->hud_cache.ply_textures[i])
			exit_game(game, "game_HUD_cache");
	}
}

/* Initialize 3D weapon */
static void	init_3D_weapon(t_game *game, int weapon_idx, char **paths, SDL_Rect *rects, int frame_count, int fire_rate)
{
	t_weapon_3D	*w = &game->hud_cache.weapons_3D[weapon_idx];

	w->fire_rate = fire_rate;
	w->frame_count = frame_count;
	w->current_frame = 0;
	w->frames = malloc(sizeof(t_weapon_3D_frame) * frame_count);
	if (!w->frames)
		exit_game(game, "malloc weapon frames");

	for (int i = 0; i < frame_count; i++)
	{
		t_png	tmp;
		tmp.path = ft_strdup(paths[i]);
		if (!process_png(&tmp))
			exit_game(game, "process png weapon 3d");
		w->frames[i].texture = create_image(&tmp, game->window->renderPTR);
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
		{600, 750, 800, 350},
		{600, 750, 800, 350},
		{600, 750, 800, 350},
		{600, 750, 800, 350}
	};

	static SDL_Rect	pistol_rects[] = {
		{820, 755, 225, 325},
		{800, 755, 225, 325}
	};

	static SDL_Rect	shotgun_rects[] = {
		{755, 830, 330, 250},
		{755, 830, 330, 250},
		{735, 830, 300, 250},
		{735, 830, 300, 250},
		{735, 830, 300, 250}
	};

	static SDL_Rect	rocket_rects[] = {
		{810, 830, 330, 250},
		{810, 830, 330, 250},
		{810, 830, 300, 250},
		{810, 830, 300, 250},
		{810, 830, 300, 250},
		{810, 830, 300, 250},
		{810, 830, 300, 250}
	};

	init_3D_weapon(game, WEAP_FISTS, fists_paths, fists_rects, 4, 12);
	init_3D_weapon(game, WEAP_PISTOL, pistol_paths, pistol_rects, 2, 18);
	init_3D_weapon(game, WEAP_SHOTGUN, shotgun_paths, shotgun_rects, 5, 20);
	init_3D_weapon(game, WEAP_ROCKET_LAUNCHER, rocket_paths, rocket_rects, 7, 20);
}

/*
	Initialize weapons, tools and player assets to keep a cache of textures
	Open and keep fonts in cache
*/
void	init_hud_cache(t_game *game)
{
	init_weapons_cache(game);
	init_tools_cache(game);
	init_player_cache(game);
	init_3D_weapons(game);

	game->hud_cache.ply_tick = 0;
	game->hud_cache.weap_tick = 0;
	game->hud_cache.text_font = TTF_OpenFont("assets/fonts/Jersey25-Regular.ttf", 25);
	game->hud_cache.number_font = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 24);
	if (!game->hud_cache.text_font || !game->hud_cache.number_font)
		exit_game(game, (char *)TTF_GetError());
}
