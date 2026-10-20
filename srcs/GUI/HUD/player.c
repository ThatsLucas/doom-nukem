/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 13:17:52 by edurance          #+#    #+#             */
/*   Updated: 2026/05/08 10:48:16 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

/* Affiche le module du portrait du joueur. */
void	display_player_module(t_game *game, int x, int y, int w, int h)
{
	SDL_Texture	*texture;
	int			frame = game->hud_cache.ply_frame;
	int			hp = game->ply->hp;
	SDL_Rect	dest = {x, y, w, h};

	to_responsive(game->window, &dest);

	if (hp <= 0)
		texture = game->hud_cache.ply_textures[STATE_DEAD];
	else if (hp > 50)
		texture = game->hud_cache.ply_textures[frame + STATE_DEFAULT];
	else if (hp > 30)
		texture = game->hud_cache.ply_textures[frame + STATE_INJURED];
	else
		texture = game->hud_cache.ply_textures[frame + STATE_BLEEDING];

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
}
