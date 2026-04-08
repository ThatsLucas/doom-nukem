/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:34:37 by edurance          #+#    #+#             */
/*   Updated: 2026/04/08 17:40:35 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	pickup_flash(t_game *game)
{
	/* flash alpha -> intensite du flash*/
	if (game->flash_alpha > 0.0f)
	{
		SDL_SetRenderDrawBlendMode(game->window->renderPTR, SDL_BLENDMODE_BLEND); // melanger les couleurs avec transparence
		SDL_SetRenderDrawColor(game->window->renderPTR, 255, 255, 255, (int)(game->flash_alpha * 255)); // defini la couleur du rectange (surtout avec la bonne intensite)

		/*  on recup la taille de l'ecran  */
		int w, h;
		get_screen_size(&w, &h);
		// SDL_GetRendererOutputSize(game->window->renderPTR, &w, &h);
		SDL_Rect fullscreen = {0, 0, w, h};
		SDL_RenderFillRect(game->window->renderPTR, &fullscreen); // dessine le rectangle

		/* on diminue le flash pour faire un effet smooth de disparition */
		game->flash_alpha -= 0.03f;
		if (game->flash_alpha < 0.0f)
			game->flash_alpha = 0.0f;
	}
}
