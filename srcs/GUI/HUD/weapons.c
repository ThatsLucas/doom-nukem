/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:07:55 by edurance          #+#    #+#             */
/*   Updated: 2026/04/11 10:38:55 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/HUD.h"

static void	display_weapon(t_game *game, int x, int y)
{
	t_inventory *inv = &game->ply->inventory;
	t_weapon	*current = &inv->weapons[game->ply->current_weap_index];
	char	*path;
	SDL_Rect weapon_dest;

	weapon_dest.y = y;
	if (current->type == WEAP_FISTS)
	{
		path = "assets/png/hud/weapons/fist.bmp";
		weapon_dest.w = 100;
		weapon_dest.h = 90;
		weapon_dest.x = x + 10;
	}
	else if (current->type == WEAP_PISTOL)
	{
		path = "assets/png/hud/weapons/pistol.bmp";
		weapon_dest.w = 130;
		weapon_dest.h = 100;
		weapon_dest.x = x;
	}
	if (current->type == WEAP_SHOTGUN)
	{
		path = "assets/png/hud/weapons/shotgun.bmp";
		weapon_dest.w = 190;
		weapon_dest.h = 90;
		weapon_dest.x = x - 35;
		weapon_dest.y = y - 10;
	}
	if (current->type == WEAP_ROCKET_LAUNCHER)
	{
		path = "assets/png/hud/weapons/rocket.bmp";
		weapon_dest.w = 250;
		weapon_dest.h = 60;
		weapon_dest.x = x - 60;
	}

	SDL_Surface	*surface_weapon = SDL_LoadBMP(path);
	if (!surface_weapon)
		exit_game(game, "surface weapon");

	SDL_Texture	*weapon_texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_weapon);
	SDL_FreeSurface(surface_weapon);
	SDL_RenderCopy(game->window->renderPTR, weapon_texture, NULL, &weapon_dest);
}

static void	display_weapons(t_game *game, int x, int y, int w, int h)
{
	TTF_Font *weapons_font = TTF_OpenFont("assets/fonts/Jersey25-Regular.ttf", 25);
	if (!weapons_font)
			exit_game(game, (char *)TTF_GetError());

	SDL_Color weapons_color = {255, 255, 255, 255};
	SDL_Rect Message_Rect;
	Message_Rect.x = x;
	Message_Rect.y = y;
	Message_Rect.h = h;
	Message_Rect.w = w;

	SDL_Surface *surface_health = TTF_RenderText_Solid(weapons_font, "WEAPONS", weapons_color);
	if (!surface_health)
		exit_game(game, (char *)TTF_GetError());
	SDL_Texture *Message = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_health);

	SDL_RenderCopy(game->window->renderPTR, Message, NULL, &Message_Rect);
	TTF_CloseFont(weapons_font);
}

void	display_module_weapons(t_game *game, int x, int y, int w, int h)
{
	display_weapons(game, x, y, w, h);
	display_weapon(game, x + 55, y + 70);
}
