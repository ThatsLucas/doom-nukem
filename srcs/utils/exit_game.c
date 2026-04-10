/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:57:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/09 21:26:00 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	exit_game(t_game *game, char *type)
{
	const char	*error = SDL_GetError();

	if (type && error && error[0])
	{
		ft_putstr_fd(type, STDERR_FILENO);
		ft_putstr_fd(" => ", STDERR_FILENO);
		ft_putstr_fd((char *)error, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}

	if (game->window->buttonList)
		free_buttons(game->window->buttonList);
	if (game->window && game->window->renderPTR)
		SDL_DestroyRenderer(game->window->renderPTR);
	if (game->window && game->window->winPTR)
		SDL_DestroyWindow(game->window->winPTR);
	free(game->window);
	free(game->ply);
	free_bsp(game->bspTree);
	ft_lstclear(&game->walls, &free);
	free(game);
	SDL_Quit();
	ft_printf("And thanks for all the fish!\n");
	exit(0);
}
