/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:23:50 by edurance          #+#    #+#             */
/*   Updated: 2026/05/07 12:30:35 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/HUD.h"

void	draw_minimap(SDL_Renderer *render, t_game *game)
{
	SDL_SetRenderTarget(render, game->minimap_tex);
	SDL_SetRenderDrawColor(render, 20, 20, 20, 220);
	SDL_RenderClear(render);

	SDL_Rect clip = {0, 0, MINI_W, MINI_H};
	to_responsive(game->window, &clip);
	SDL_RenderSetClipRect(render, &clip);

	draw_minimap_walls(game, render);

	t_RGB green = {37, 184, 29, 255};
	draw_player_minimap(render, game, 7, green);

	SDL_RenderSetClipRect(render, NULL);
	SDL_SetRenderTarget(render, NULL);

	SDL_SetTextureAlphaMod(game->minimap_tex, 210);
	SDL_Rect dest = {MINI_X, MINI_Y, MINI_W, MINI_H};
	to_responsive(game->window, &dest);
	SDL_RenderCopy(render, game->minimap_tex, NULL, &dest);
}
