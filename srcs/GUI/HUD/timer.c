/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:25:51 by edurance          #+#    #+#             */
/*   Updated: 2026/04/11 10:39:42 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/HUD.h"

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

void	display_timer(t_game *game, int x, int y, int w, int h, t_RGB rgb)
{
	TTF_Font *font = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 24);
	if (!font)
			exit_game(game, (char *)TTF_GetError());

	SDL_Color font_color = {rgb.r, rgb.g, rgb.b, rgb.alphaValue};
	SDL_Rect Message_Rect;
	Message_Rect.x = x;
	Message_Rect.y = y;
	Message_Rect.h = h;
	Message_Rect.w = w;
	char	buf[6];
	get_timer(buf);

	SDL_Surface *surface_message = TTF_RenderText_Solid(font, buf, font_color);
	if (!surface_message)
		exit_game(game, (char *)TTF_GetError());
	SDL_Texture *Message = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_message);

	SDL_RenderCopy(game->window->renderPTR, Message, NULL, &Message_Rect);
	TTF_CloseFont(font);
}
