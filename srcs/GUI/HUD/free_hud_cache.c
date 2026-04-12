/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hud_cache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:41 by edurance          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:59 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

void	free_hud_cache(t_game *game)
{
	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		if (game->hud_cache.weapon_textures[i])
			SDL_DestroyTexture(game->hud_cache.weapon_textures[i]);
	}
	if (game->hud_cache.weapons_font)
		TTF_CloseFont(game->hud_cache.weapons_font);
}
