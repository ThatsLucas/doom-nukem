/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:10:13 by edurance          #+#    #+#             */
/*   Updated: 2026/04/12 13:18:54 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/HUD.h"

static void	display_tools_png(t_game *game, int x, int y)
{
	t_inventory *inv = &game->ply->inventory;

	for (int i = 0; i < MAX_TOOLS; i++)
		SDL_SetTextureAlphaMod(game->hud_cache.tools_textures[i], 50);

	for (int i = 0; i < inv->tool_count; i++)
	{
		int	type = inv->tools[i].type;
		if (type < MAX_TOOLS)
			SDL_SetTextureAlphaMod(game->hud_cache.tools_textures[type], 255);
	}

	static const int	layout[][4] = {
		[TOOL_FLASHLIGHT] = {130, 15, 100, 34},
		[TOOL_KEY] = {  0,  0,  70, 70},
		[TOOL_JETPACK] = { 60,-10,  80, 80},
	};

	for (int i = 0; i < MAX_TOOLS; i++)
	{
		SDL_Rect	dest = {x + layout[i][0], y + layout[i][1], .w = layout[i][2], .h = layout[i][3]};
		SDL_RenderCopy(game->window->renderPTR, game->hud_cache.tools_textures[i], NULL, &dest);
	}
}

static void	display_tools(t_game *game, int x, int y, int w, int h)
{
	SDL_Color color = {255, 255, 255, 255};
	SDL_Rect dest = {x, y, w, h};

	SDL_Surface *surface = TTF_RenderText_Solid(game->hud_cache.text_font, "TOOLS", color);
	if (!surface)
		exit_game(game, (char *)TTF_GetError());

	SDL_Texture *texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		exit_game(game, (char *)SDL_GetError());

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
}

void	display_module_tools(t_game *game, int x, int y, int w, int h)
{
	display_tools(game, x, y, w, h);
	display_tools_png(game, x, y + 80);
}
