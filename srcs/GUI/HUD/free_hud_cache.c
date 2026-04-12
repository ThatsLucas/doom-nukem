/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hud_cache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:41 by edurance          #+#    #+#             */
/*   Updated: 2026/04/12 11:39:37 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

void	free_hud_cache(t_game *game)
{
	if (game->hud_cache.text_font)
		TTF_CloseFont(game->hud_cache.text_font);
	if (game->hud_cache.number_font)
		TTF_CloseFont(game->hud_cache.number_font);
}
