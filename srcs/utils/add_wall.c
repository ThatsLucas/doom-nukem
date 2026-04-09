/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:37:13 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/09 12:05:02 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	add_wall(t_game *game)
{
	t_coordinates	mouseCoords;
	t_wall			*wall;

	SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
	wall = calloc(1, sizeof(t_wall));
	if (!wall)
		exit_game(game, "add_wall");
	wall->coords.x = to_PosX(mouseCoords.x, game);
	wall->coords.y = to_PosY(mouseCoords.y, game);
	ft_lstadd_back(&game->walls, ft_lstnew(wall));
	// printf("wall ajoute en %f, %f\n", wall->coords.x, wall->coords.y);
	return ;
}

void	rm_last_wall(t_game *game)
{
	t_list	*last, *previous;

	if (!game->walls)
		return ;

	last = ft_lstlast(game->walls);
	previous = last->previous;

	if (previous)
		previous->next = NULL;
	else
		game->walls = NULL;
	ft_lstdelone(last, &free);

	return ;
}
