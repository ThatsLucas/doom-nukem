/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ammo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:23:43 by edurance          #+#    #+#             */
/*   Updated: 2026/04/11 10:40:02 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/HUD.h"

static void	display_ammo_nb(t_game *game, int x, int y, int w, int h)
{
	TTF_Font *ammo_font = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 20);
	if (!ammo_font)
			exit_game(game, (char *)TTF_GetError());

	SDL_Color ammo_color = {150, 0, 0, 255};
	SDL_Rect Message_Rect;
	Message_Rect.x = x;
	Message_Rect.y = y;
	Message_Rect.h = h;
	Message_Rect.w = w;

	SDL_Surface *surface_ammo;
	char *buf;
	int ammo = game->ply->inventory.weapons[game->ply->current_weap_index].ammo;
	buf = ft_itoa(ammo);
	if (!buf)
		exit_game(game, "ammo display");
	if (ammo < 0)
	{
		free(buf);
		buf = "Infinite";
		surface_ammo = TTF_RenderText_Solid(ammo_font, buf, ammo_color);
	}
	else
	{
		surface_ammo = TTF_RenderText_Solid(ammo_font, buf, ammo_color);
		free(buf);
	}

	if (!surface_ammo)
		exit_game(game, (char *)TTF_GetError());
	SDL_Texture *Message = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_ammo);

	SDL_RenderCopy(game->window->renderPTR, Message, NULL, &Message_Rect);
	TTF_CloseFont(ammo_font);
}

static void	display_ammo(t_game *game, int x, int y, int w, int h)
{
	TTF_Font *ammo_font = TTF_OpenFont("assets/fonts/Jersey25-Regular.ttf", 25);
	if (!ammo_font)
			exit_game(game, (char *)TTF_GetError());

	SDL_Color ammo_color = {255, 255, 255, 255};
	SDL_Rect Message_Rect;
	Message_Rect.x = x;
	Message_Rect.y = y;
	Message_Rect.h = h;
	Message_Rect.w = w;

	SDL_Surface *surface_ammo = TTF_RenderText_Solid(ammo_font, "AMMO", ammo_color);
	if (!surface_ammo)
		exit_game(game, (char *)TTF_GetError());
	SDL_Texture *Message = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_ammo);

	SDL_RenderCopy(game->window->renderPTR, Message, NULL, &Message_Rect);
	TTF_CloseFont(ammo_font);
}

void	display_module_ammo(t_game *game, int x, int y, int w, int h)
{
	display_ammo(game, x, y, w, h);
	display_ammo_nb(game, x + 10, y + 80, w - 20, h);
}
