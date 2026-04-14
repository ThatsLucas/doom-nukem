/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 16:25:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/14 23:12:13 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

t_game	*init_game(void)
{
	t_game	*game;
	int		w = 1920, h = 1080;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_bzero(game, sizeof(t_game));

	if (TTF_Init() < 0)
		exit_game(game, "TTF Init");

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS))
		exit_game(game, "SDL_INIT");
	// get_screen_size(&w, &h);
	game->window = create_window("Doom Nukem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL );
	if (!game->window)
		exit_game(game, "create_window");
	game->ply = malloc(sizeof(t_ply));
	if (!game->ply)
		exit_game(game, "player malloc");
	game->window->PopupPtr.notif_buf = NULL;
	return (game);
}
