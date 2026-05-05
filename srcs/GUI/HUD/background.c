/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:35:42 by edurance          #+#    #+#             */
/*   Updated: 2026/05/05 12:36:14 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

/* To display the gray background for the hud */
void	display_hud_bg(t_game *game)
{
	SDL_Rect	dest = {
		.h = 190,
		.w = 1920,
		.x = 0,
		.y = 1080 - 190
	};
	to_responsive(game->window, &dest);
	SDL_RenderCopy(game->window->renderPTR, game->hud_cache.bg_texture, NULL, &dest);
}
