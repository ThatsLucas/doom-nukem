/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hud_cache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:41 by edurance          #+#    #+#             */
/*   Updated: 2026/05/08 10:12:24 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

/* Function to free hud cache (especially fonts, cause textures are freed with the renderer) */
void	free_hud_cache(t_game *game)
{
	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		t_weapon_3D *w = &game->hud_cache.weapons_3D[i];
		for (int j = 0; j < w->frame_count; j++)
			SDL_DestroyTexture(w->frames[j].texture);
		free(w->frames);
		w->frames = NULL;
	}

	if (game->hud_cache.text_font)
		TTF_CloseFont(game->hud_cache.text_font);
	if (game->hud_cache.number_font)
		TTF_CloseFont(game->hud_cache.number_font);
}
