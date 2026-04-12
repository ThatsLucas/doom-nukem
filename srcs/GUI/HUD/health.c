/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:12:27 by edurance          #+#    #+#             */
/*   Updated: 2026/04/12 12:19:50 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

static void	display_hp(t_game *game, int x, int y, int w, int h)
{
	SDL_Color color = {150, 0, 0, 255};
	SDL_Rect dest = {x, y, w, h};

	char *buf = ft_itoa(game->ply->hp);
	if (!buf)
		exit_game(game, "hp display");

	SDL_Surface *surface = TTF_RenderText_Solid(game->hud_cache.number_font, buf, color);
	free(buf);
	if (!surface)
		exit_game(game, (char *)TTF_GetError());

	SDL_Texture *texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		exit_game(game, (char *)SDL_GetError());

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
}

static void	display_health(t_game *game, int x, int y, int w, int h)
{
	SDL_Color color = {255, 255, 255, 255};
	SDL_Rect dest = {x, y, w, h};

	SDL_Surface *surface = TTF_RenderText_Solid(game->hud_cache.text_font, "HEALTH", color);
	if (!surface)
		exit_game(game, (char *)TTF_GetError());

	SDL_Texture *texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		exit_game(game, (char *)SDL_GetError());

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
}

void	display_module_health(t_game *game, int x, int y, int w, int h)
{
	display_health(game, x, y, w, h);
	display_hp(game, x + 10, y + 80, w - 50, h);
}
