/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_cache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:30:07 by edurance          #+#    #+#             */
/*   Updated: 2026/04/12 09:43:19 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "inventory/Items.h"
#include "parser/PNG.h"
#include "Game.h"

void	init_hud_cache(t_game *game)
{
	static char	*paths[MAX_WEAPONS] = {
		"assets/png/hud/weapons/fist.png",
		"assets/png/hud/weapons/pistol.png",
		"assets/png/hud/weapons/shotgun.png",
		"assets/png/hud/weapons/rocket.png",
	};
	t_png	tmp;

	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		if (!process_png(&tmp, paths[i]))
			exit_game(game, "process png");
		game->hud_cache.weapon_textures[i] = create_image(&tmp, game->window->renderPTR);
	}
	game->hud_cache.weapons_font = 	TTF_OpenFont("assets/fonts/Jersey25-Regular.ttf", 25);
	if (!game->hud_cache.weapons_font)
		exit_game(game, (char *)TTF_GetError());
}
