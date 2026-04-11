/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:12:27 by edurance          #+#    #+#             */
/*   Updated: 2026/04/11 10:40:38 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

static void	display_hp(t_game *game, int x, int y, int w, int h)
{
	TTF_Font *hp_font = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 25);
	if (!hp_font)
			exit_game(game, (char *)TTF_GetError());

	SDL_Color hp_color = {150, 0, 0, 255};
	SDL_Rect Message_Rect;
	Message_Rect.x = x;
	Message_Rect.y = y;
	Message_Rect.h = h;
	Message_Rect.w = w;

	char *buf = ft_itoa(game->ply->hp);
	if (!buf)
		exit_game(game, "hp display");
	SDL_Surface *surface_health = TTF_RenderText_Solid(hp_font, buf, hp_color);
	free(buf);
	if (!surface_health)
		exit_game(game, (char *)TTF_GetError());
	SDL_Texture *Message = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_health);

	SDL_RenderCopy(game->window->renderPTR, Message, NULL, &Message_Rect);
	TTF_CloseFont(hp_font);
}

static void	display_health(t_game *game, int x, int y, int w, int h)
{
	TTF_Font *health_font = TTF_OpenFont("assets/fonts/Jersey25-Regular.ttf", 25);
	if (!health_font)
			exit_game(game, (char *)TTF_GetError());

	SDL_Color health_color = {255, 255, 255, 255};
	SDL_Rect Message_Rect;
	Message_Rect.x = x;
	Message_Rect.y = y;
	Message_Rect.h = h;
	Message_Rect.w = w;

	SDL_Surface *surface_health = TTF_RenderText_Solid(health_font, "HEALTH", health_color);
	if (!surface_health)
		exit_game(game, (char *)TTF_GetError());
	SDL_Texture *Message = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_health);

	SDL_RenderCopy(game->window->renderPTR, Message, NULL, &Message_Rect);
	TTF_CloseFont(health_font);
}

void	display_module_health(t_game *game, int x, int y, int w, int h)
{
	display_health(game, x, y, w, h);
	display_hp(game, x + 10, y + 80, w - 50, h);
}
