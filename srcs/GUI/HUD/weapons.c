/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:07:55 by edurance          #+#    #+#             */
/*   Updated: 2026/04/12 12:16:02 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "parser/PNG.h"
#include "GUI/HUD.h"

static void	display_weapon(t_game *game, int x, int y)
{
	static const int	layout[][4] = {
		[WEAP_FISTS] = {10, 0, 100, 90},
		[WEAP_PISTOL] = {0, 0, 130, 100},
		[WEAP_SHOTGUN] = {-35, -10, 190, 90},
		[WEAP_ROCKET_LAUNCHER] = {-60, 0, 250, 60}
	};

	int				idx = game->ply->current_weap_index;
	t_weapon_type	type = game->ply->inventory.weapons[idx].type;
	SDL_Rect		dest = {x + layout[type][0], y + layout[type][1], layout[type][2], layout[type][3]};

	SDL_RenderCopy(game->window->renderPTR, game->hud_cache.weapon_textures[type], NULL, &dest);
}

static void	display_weapons(t_game *game, int x, int y, int w, int h)
{
	SDL_Color	fg = {255, 255, 255, 255};
	SDL_Rect	rect = {x, y, w, h};

	SDL_Surface	*surface = TTF_RenderText_Solid(game->hud_cache.text_font, "WEAPONS", fg);
	if (!surface)
		exit_game(game, (char *)TTF_GetError());

	SDL_Texture	*texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		exit_game(game, (char *)SDL_GetError());

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &rect);
}

void	display_module_weapons(t_game *game, int x, int y, int w, int h)
{
	display_weapons(game, x, y, w, h);
	display_weapon(game, x + 55, y + 70);
}
