/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_cache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:30:07 by edurance          #+#    #+#             */
/*   Updated: 2026/06/08 12:16:33 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "inventory/Items.h"
#include "parser/PNG.h"
#include "Game.h"

/* Loads a gauge and its unit texture (battery, fuel) into dst[0] and dst[1] */
static void	init_hud_gauge(t_game *game, char **paths, SDL_Texture **dst, char **errors)
{
	t_png	gauge;
	t_png	unit;

	gauge.path = ft_strdup(paths[0]);
	unit.path = ft_strdup(paths[1]);

	if (!process_png(&gauge) || !process_png(&unit))
		exit_game(game, errors[0]);

	dst[0] = create_image(&gauge, game->window->renderPTR);
	dst[1] = create_image(&unit, game->window->renderPTR);
	if (!dst[0] || !dst[1])
		exit_game(game, errors[1]);
}

static void	init_hud_background(t_game *game)
{
	t_png	hud_bg;

	hud_bg.path = ft_strdup("assets/png/hud/hudbg.png");
	if (!process_png(&hud_bg))
		exit_game(game, "Error loading hud bg: process failed");
	game->hud_cache.bg_texture = create_image(&hud_bg, game->window->renderPTR);
	if (!game->hud_cache.bg_texture)
		exit_game(game, "Error loading hud bg: create image failed");
}

/*
	Initialize weapons, tools and player assets to keep a cache of textures
	Open and keep fonts in cache
*/
void	init_hud_cache(t_game *game)
{
	init_3D_weapons(game);
	init_all_assets(game);
	init_hud_background(game);
	init_hud_gauge(game,
		(char *[2]){"assets/png/hud/tools/battery_gauge.png", "assets/png/hud/tools/battery_unit.png"},
		game->hud_cache.battery,
		(char *[2]){"Error loading hud battery: process failed", "Error loading hud battery: create image failed"});
	init_hud_gauge(game,
		(char *[2]){"assets/png/hud/tools/fuel_gauge.png", "assets/png/hud/tools/fuel_unit.png"},
		game->hud_cache.fuel,
		(char *[2]){"Error loading hud fuel: process failed", "Error loading hud fuel: create image failed"});

	game->hud_cache.text_font = TTF_OpenFont("assets/fonts/Jersey25-Regular.ttf", 25);
	game->hud_cache.number_font = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 24);
	game->hud_cache.ply_last_time = get_time_ms();
	game->hud_cache.ply_frame = 0;
	if (!game->hud_cache.text_font || !game->hud_cache.number_font)
		exit_game(game, (char *)TTF_GetError());
}
