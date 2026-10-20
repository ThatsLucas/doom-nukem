/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ammo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:23:43 by edurance          #+#    #+#             */
/*   Updated: 2026/10/20 16:31:42 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/HUD.h"

/* Affiche le nombre de munitions de l’arme (rien pour les poings). */
static void	display_ammo_nb(t_game *game, int x, int y, int w, int h)
{
	char *buf;
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	SDL_Color	color = {150, 0, 0, 255};
	SDL_Rect	dest = {x, y, w, h};

	to_responsive(game->window, &dest);
	int ammo = game->ply->inventory.weapons[game->ply->current_weap_index].ammo;

	if (ammo < 0)
		buf = "Infinite";
	else
	{
		buf = ft_itoa(ammo);
		if (!buf)
			exit_game(game, "ammo display");
	}

	surface = TTF_RenderText_Solid(game->hud_cache.number_font, buf, color);

	if (ammo >= 0)
		free(buf);

	if (!surface)
		exit_game(game, (char *)TTF_GetError());

	texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		exit_game(game, (char *)SDL_GetError());

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
}

/* Affiche le libellé « AMMO ». */
static void	display_ammo(t_game *game, int x, int y, int w, int h)
{
	SDL_Color color = {255, 255, 255, 255};
	SDL_Rect dest = {x, y, w, h};

	to_responsive(game->window, &dest);
	SDL_Surface *surface = TTF_RenderText_Solid(game->hud_cache.text_font, "AMMO", color);
	if (!surface)
		exit_game(game, (char *)TTF_GetError());

	SDL_Texture *texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		exit_game(game, (char *)SDL_GetError());

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
}

/* Affiche le module des munitions du HUD. */
void	display_module_ammo(t_game *game, int x, int y, int w, int h)
{
	display_ammo(game, x, y, w, h);
	display_ammo_nb(game, x + 10, y + 80, w - 20, h);
}
