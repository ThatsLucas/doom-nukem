/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_cache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:30:07 by edurance          #+#    #+#             */
/*   Updated: 2026/04/13 12:20:00 by edurance         ###   ########.fr       */
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

	t_png	tmp;
	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		if (!process_png(&tmp, weap_paths[i]))
			exit_game(game, "process png");
		game->hud_cache.weapon_textures[i] = create_image(&tmp, game->window->renderPTR);
		if (!game->hud_cache.weapon_textures[i])
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

	t_png	tmp;
	for (int i = 0; i < MAX_TOOLS; i++)
	{
		if (!process_png(&tmp, tools_paths[i]))
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

	t_png	tmp;
	for (int i = 0; i < 10; i++)
	{
		if (!process_png(&tmp, player_paths[i]))
			exit_game(game, "process png");
		game->hud_cache.ply_textures[i] = create_image(&tmp, game->window->renderPTR);
		if (!game->hud_cache.ply_textures[i])
			exit_game(game, "game_HUD_cache");
	}
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

	game->hud_cache.ply_tick = 0;
	game->hud_cache.text_font = TTF_OpenFont("assets/fonts/Jersey25-Regular.ttf", 25);
	game->hud_cache.number_font = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 24);
	if (!game->hud_cache.text_font || !game->hud_cache.number_font)
		exit_game(game, (char *)TTF_GetError());
}
