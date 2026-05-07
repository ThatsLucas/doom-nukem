/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:41:42 by edurance          #+#    #+#             */
/*   Updated: 2026/05/07 15:59:07 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

/*Recuperer la timestamp actuelle en ms*/
static long get_timestamp(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

/* Afficher les fps en haut a droite de l'ecran */
void	display_fps(t_game *game)
{
	static int fps = 0;
	static long last_time = 0;
	long time;

	time = get_timestamp();
	if (!last_time)
	{
		last_time = time;
		return;
	}
	if (last_time + 1000 <= time)
	{
		free(game->fps);
		game->fps = NULL;
		game->fps = ft_itoa(fps);
		last_time = time;
		fps = 1;
	}
	else
		fps++;

	SDL_Color color = {255, 255, 255, 255};
	
	{
		SDL_Rect dest = {1735, 35, 70, 25};
		to_responsive(game->window, &dest);
		char *buf = ft_strdup("FPS ");

		SDL_Surface *surface = TTF_RenderText_Solid(game->hud_cache.text_font, buf, color);
		free(buf);
		if (!surface)
			exit_game(game, (char *)TTF_GetError());

		SDL_Texture *texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface);
		SDL_FreeSurface(surface);
		if (!texture)
			exit_game(game, (char *)SDL_GetError());

		SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
	}
	{
		if (!game->fps)
			game->fps = ft_itoa(100);
	
		SDL_Rect dest = {1805, 35, 65, 25};
		to_responsive(game->window, &dest);
		char *buf = ft_strdup(game->fps);

		SDL_Surface *surface = TTF_RenderText_Solid(game->hud_cache.text_font, buf, color);
		free(buf);
		if (!surface)
			exit_game(game, (char *)TTF_GetError());

		SDL_Texture *texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface);
		SDL_FreeSurface(surface);
		if (!texture)
			exit_game(game, (char *)SDL_GetError());

		SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
	}
}
