/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hud_cache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:41 by edurance          #+#    #+#             */
/*   Updated: 2026/07/17 14:43:59 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

/* Function to free hud cache (fonts are closed here; textures are freed by SDL_DestroyRenderer) */
void	free_hud_cache(t_game *game)
{
	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		t_weapon_3D *w = &game->hud_cache.weapons_3D[i];
		free(w->frames);
		w->frames = NULL;
		w->frame_count = 0;
	}

	if (game->hud_cache.text_font)
		TTF_CloseFont(game->hud_cache.text_font);
	if (game->hud_cache.number_font)
		TTF_CloseFont(game->hud_cache.number_font);
}
