/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_cache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:30:07 by edurance          #+#    #+#             */
/*   Updated: 2026/04/12 11:47:40 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "inventory/Items.h"
#include "parser/PNG.h"
#include "Game.h"

void	init_hud_cache(t_game *game)
{
	static char	*weap_paths[MAX_WEAPONS] = {
		"assets/png/hud/weapons/fist.png",
		"assets/png/hud/weapons/pistol.png",
		"assets/png/hud/weapons/shotgun.png",
		"assets/png/hud/weapons/rocket.png",
	};

	static char	*tools_paths[MAX_TOOLS] = {
		"assets/png/hud/tools/flashlight.png",
		"assets/png/hud/tools/key.png",
		"assets/png/hud/tools/jetpack.png",
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

	for (int i = 0; i < MAX_TOOLS; i++)
	{
		if (!process_png(&tmp, tools_paths[i]))
			exit_game(game, "process png");
		game->hud_cache.tools_texture[i] = create_image(&tmp, game->window->renderPTR);
		if (!game->hud_cache.tools_texture[i])
			exit_game(game, "game_HUD_cache");
	}

	game->hud_cache.text_font = TTF_OpenFont("assets/fonts/Jersey25-Regular.ttf", 25);
	game->hud_cache.number_font = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 24);
	if (!game->hud_cache.text_font || !game->hud_cache.number_font)
		exit_game(game, (char *)TTF_GetError());
}
