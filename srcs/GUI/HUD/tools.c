/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:10:13 by edurance          #+#    #+#             */
/*   Updated: 2026/04/11 11:23:09 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/HUD.h"

static void	display_tools_png(t_game *game, int x, int y)
{
	t_inventory *inv = &game->ply->inventory;
	
	char	*key_path = "assets/png/hud/tools/key.png";
	char	*jetpack_path = "assets/png/hud/tools/jetpack.png";
	char	*flashlight_path = "assets/png/hud/tools/flashlight.png";
	
	t_png		key_png;
	t_png		jetpack_png;
	t_png		flashlight_png;

	if (!process_png(&key_png, key_path) || !process_png(&jetpack_png, jetpack_path) || !process_png(&flashlight_png, flashlight_path))
		exit_game(game, "process png");

	SDL_Texture	*key_texture = create_image(&key_png, game->window->renderPTR);
	SDL_Texture	*jetpack_texture = create_image(&jetpack_png, game->window->renderPTR);
	SDL_Texture	*flashlight_texture = create_image(&flashlight_png, game->window->renderPTR);

	SDL_SetTextureAlphaMod(key_texture, 128);
	SDL_SetTextureAlphaMod(jetpack_texture, 50);
	SDL_SetTextureAlphaMod(flashlight_texture, 128);

	for (int i = 0; i < inv->tool_count; i++)
	{
		if (inv->tools[i].type == TOOL_KEY)
			SDL_SetTextureAlphaMod(key_texture, 255);
		else if (inv->tools[i].type == TOOL_JETPACK)
			SDL_SetTextureAlphaMod(jetpack_texture, 255);
		else if (inv->tools[i].type == TOOL_FLASHLIGHT)
			SDL_SetTextureAlphaMod(flashlight_texture, 255);
	}

	SDL_Rect	key_dest = {
		.x = x,
		.y = y,
		.w = 70,
		.h = 70
	};

	SDL_Rect	jetpack_dest = {
		.x = x + 60,
		.y = y - 10,
		.w = 80,
		.h = 80
	};

	SDL_Rect	flashlight_dest = {
		.x = x + 130,
		.y = y + 15,
		.w = 100,
		.h = 34
	};

	SDL_RenderCopy(game->window->renderPTR, key_texture, NULL, &key_dest);
	SDL_RenderCopy(game->window->renderPTR, jetpack_texture, NULL, &jetpack_dest);
	SDL_RenderCopy(game->window->renderPTR, flashlight_texture, NULL, &flashlight_dest);
}

static void	display_tools(t_game *game, int x, int y, int w, int h)
{
	TTF_Font *tools_font = TTF_OpenFont("assets/fonts/Jersey25-Regular.ttf", 25);
	if (!tools_font)
			exit_game(game, (char *)TTF_GetError());

	SDL_Color tools_color = {255, 255, 255, 255};
	SDL_Rect Message_Rect;
	Message_Rect.x = x;
	Message_Rect.y = y;
	Message_Rect.h = h;
	Message_Rect.w = w;

	SDL_Surface *surface_health = TTF_RenderText_Solid(tools_font, "TOOLS", tools_color);
	if (!surface_health)
		exit_game(game, (char *)TTF_GetError());
	SDL_Texture *Message = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_health);

	SDL_RenderCopy(game->window->renderPTR, Message, NULL, &Message_Rect);
	TTF_CloseFont(tools_font);
}

void	display_module_tools(t_game *game, int x, int y, int w, int h)
{
	display_tools(game, x, y, w, h);
	display_tools_png(game, x, y + 80);
}
