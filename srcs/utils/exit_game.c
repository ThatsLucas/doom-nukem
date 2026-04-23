/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:50:07 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/22 14:48:52 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "menus/menus.h"

void	exit_game(t_game *game, char *type)
{
	const char	*error = SDL_GetError();
	t_WIN		*win;

	if (type && error && error[0])
	{
		ft_putstr_fd(type, STDERR_FILENO);
		ft_putstr_fd(" => ", STDERR_FILENO);
		ft_putstr_fd((char *)error, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (type)
	{
		ft_putstr_fd(type, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
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
	free(game);
	TTF_Quit();
	SDL_Quit();
	ft_printf("And thanks for all the fish!\n");
	exit(0);
}
