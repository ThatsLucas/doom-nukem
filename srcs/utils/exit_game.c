/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:57:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/05 16:20:46 by aabouyaz         ###   ########.fr       */
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

	if (game->window && game->window->renderPTR)
		SDL_DestroyRenderer(game->window->renderPTR);
	if (game->window && game->window->winPTR)
		SDL_DestroyWindow(game->window->winPTR);
	free(game->window);
	SDL_Quit();
	exit(0);
}
