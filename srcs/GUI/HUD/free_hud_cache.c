/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hud_cache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:41 by edurance          #+#    #+#             */
/*   Updated: 2026/04/13 10:08:21 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

/* Function to free hud cache (especially fonts, cause textures are freed with the renderer) */
void	free_hud_cache(t_game *game)
{
	if (game->hud_cache.text_font)
		TTF_CloseFont(game->hud_cache.text_font);
	if (game->hud_cache.number_font)
		TTF_CloseFont(game->hud_cache.number_font);
}
