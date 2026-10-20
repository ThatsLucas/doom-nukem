/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:25:51 by edurance          #+#    #+#             */
/*   Updated: 2026/04/13 11:40:20 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/HUD.h"

/* Formate une durée au format minutes et secondes. */
static void	format_time(long total_seconds, char *buf)
{
	int	minutes = total_seconds / 60;
	int	seconds = total_seconds % 60;
	
	buf[0] = minutes / 10 + '0';
	buf[1] = minutes % 10 + '0';
	buf[2] = ':';
	buf[3] = seconds / 10 + '0';
	buf[4] = seconds % 10 + '0';
	buf[5] = '\0';
}

/* Récupère le temps écoulé depuis le début de la partie. */
static void	get_timer(char *buf)
{
	static struct timeval	start;
	static int				init = 0;
	struct timeval			now;
	struct timezone			*tz = 0;

	if (!init)
	{
		gettimeofday(&start, tz);
		init = 1;
	}

	gettimeofday(&now, tz);
	long	elapsed = now.tv_sec - start.tv_sec;
	format_time(elapsed, buf);
}

/* Affiche le temps de jeu écoulé. */
void	display_timer(t_game *game, int x, int y, int w, int h, t_RGB rgb)
{
	SDL_Color fg = {rgb.r, rgb.g, rgb.b, rgb.alphaValue};
	SDL_Rect dest = {x, y, w, h};
	char	buf[6];

	get_timer(buf);
	to_responsive(game->window, &dest);

	SDL_Surface *surface = TTF_RenderText_Solid(game->hud_cache.number_font, buf, fg);
	if (!surface)
		exit_game(game, (char *)TTF_GetError());

	SDL_Texture *texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		exit_game(game, (char *)SDL_GetError());

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
}
