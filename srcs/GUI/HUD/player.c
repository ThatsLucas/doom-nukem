/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 13:17:52 by edurance          #+#    #+#             */
/*   Updated: 2026/04/12 13:56:47 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

void	update_hud_anim(t_game *game)
{
	game->hud_cache.ply_tick++;
	if (game->hud_cache.ply_tick >= 120)
	{
		game->hud_cache.ply_tick = 0;
		game->hud_cache.ply_frame = (game->hud_cache.ply_frame + 1) % 2;
	}
}

void	display_player_module(t_game *game, int x, int y, int w, int h)
{
	SDL_Texture	*texture;
	int			frame = game->hud_cache.ply_frame;
	int			hp = game->ply->hp;
	SDL_Rect	dest = {x, y, w, h};

	if (hp <= 0)
		texture = game->hud_cache.ply_textures[5];
	else if (hp > 50)
		texture = game->hud_cache.ply_textures[frame];
	else
		texture = game->hud_cache.ply_textures[2 + frame];

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
}
