/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:41:42 by edurance          #+#    #+#             */
/*   Updated: 2026/07/07 02:29:13 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

/* Récupère l’horodatage actuel. */
long	get_timestamp(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

/* Affiche un libellé du HUD à la position indiquée. */
static void	draw_hud_label(t_game *game, char *str, SDL_Rect dest)
{
	SDL_Color color = {255, 255, 255, 255};

	to_responsive(game->window, &dest);
	char *buf = ft_strdup(str);

	SDL_Surface *surface = TTF_RenderText_Solid(game->hud_cache.text_font, buf, color);
	free(buf);
	if (!surface)
		exit_game(game, (char *)TTF_GetError());

	SDL_Texture *texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		exit_game(game, (char *)SDL_GetError());

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
}

/* Met à jour les FPS. */
static int	update_fps(t_game *game)
{
	static int fps = 0;
	static long last_time = 0;
	long time;

	time = get_timestamp();
	if (!last_time)
	{
		last_time = time;
		return (0);
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
	return (1);
}

/* Affiche le compteur de FPS. */
void	display_fps(t_game *game)
{
	if (!update_fps(game))
		return;

	draw_hud_label(game, "FPS ", (SDL_Rect){1735, 35, 70, 25});
	if (!game->fps)
		game->fps = ft_itoa(100);
	draw_hud_label(game, game->fps, (SDL_Rect){1805, 35, 65, 25});
}
