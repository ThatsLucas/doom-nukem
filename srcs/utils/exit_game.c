/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:50:07 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/21 13:50:12 by lle-duc          ###   ########.fr       */
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
<<<<<<< HEAD
<<<<<<< HEAD
	else if (type)
	{
		ft_putstr_fd(type, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}

	cleanup_items(game);
	free_hud_cache(game);

	while (game->window->PopupPtr.notif_buf)
		destroy_notif_node(&game->window->PopupPtr.notif_buf);
=======
	while (game->window->menus.notif.notif_buf)
		destroy_notif_node(&game->window->menus.notif.notif_buf);
>>>>>>> 2c8c80d (feat (settings / gui): Reworked how menus are choosen on the sreen, added settings menu begin)
	if (game->window->buttonList)
		free_buttons(game->window->buttonList);
	free(game->ply);

	free_map(game->map);
	free(game->rays);
	free(game->fps);

	if (game->window && game->window->renderPTR)
		SDL_DestroyRenderer(game->window->renderPTR);
	if (game->window && game->window->winPTR)
		SDL_DestroyWindow(game->window->winPTR);
	free(game->window);

=======
	if (!game)
		exit(1);
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
	free(game->ply);
>>>>>>> f9e42e3 (feat (settings): fixed crash when no img found and begin slider)
	free(game);
	TTF_Quit();
	SDL_Quit();
	ft_printf("And thanks for all the fish!\n");
	exit(0);
}
