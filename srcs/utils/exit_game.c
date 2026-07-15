/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:57:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/29 11:21:41 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "menus/menus.h"

void exit_game(t_game *game, char *type)
{
	const char *error = SDL_GetError();
	t_WIN *win;

	if (type && error && error[0])
	{
		ft_dprintf(STDERR_FILENO, "%s => %s\n", type, error);
	}
	else if (type)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", type);
	}

	if (!game)
		exit(1);

	cleanup_items(game);
	free_hud_cache(game);

	free(game->ply);
	free_map(game->map);
	free(game->rays);
	free(game->fps);
	free_languages(game);
	pthread_cancel(game->serverThread);
	pthread_join(game->serverThread, NULL);
	close(game->serverStatus.serverSocket);

	win = game->window;
	if (win)
	{
		while (win->menus.notif.notif_buf)
			destroy_notif_node(&win->menus.notif.notif_buf);
		if (win->buttonList)
			free_buttons(win->buttonList);
		if (win->renderPTR)
			SDL_DestroyRenderer(win->renderPTR);
		if (win->winPTR)
			SDL_DestroyWindow(win->winPTR);
		free(win);
	}
	exit_editor(game);
	free(game);
	TTF_Quit();
	SDL_Quit();
	ft_printf("And thanks for all the fish!\n");
	exit(0);
}
