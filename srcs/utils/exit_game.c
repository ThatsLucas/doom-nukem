/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:57:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/13 22:42:25 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	free_map(t_map *map)
{
	for (int i = 0; i < map->num_textures; i++)
		SDL_FreeSurface(map->surface[i]);
			for (int i = 0; i < map->num_textures; i++)
		free(map->text_colors[i]);
	free(map->text_colors);
	free(map);
	map = NULL;

	return;
}

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
	free(game->ply);

	free_map(game->map);
	free(game->rays);
	free(game->fps);

	if (game->window && game->window->renderPTR)
		SDL_DestroyRenderer(game->window->renderPTR);
	if (game->window && game->window->winPTR)
		SDL_DestroyWindow(game->window->winPTR);
	free(game->window);

	free(game);
	SDL_Quit();
	ft_printf("And thanks for all the fish!\n");
	exit(0);
}
