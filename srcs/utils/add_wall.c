/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:37:13 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/13 22:39:54 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

// void	add_wall(t_game *game, float transparency)
// {
// 	t_coordinates	mouseCoords;
// 	t_wall			*wall, *pwall, *first;
// 	t_list			*new;

// 	SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
// 	wall = calloc(1, sizeof(t_wall));
// 	if (!wall)
// 		exit_game(game, "add_wall");
// 	wall->end.x = to_PosX(mouseCoords.x, game);
// 	wall->end.y = to_PosY(mouseCoords.y, game);
// 	wall->transparency = transparency;
// 	wall->textureID = rand() % 2;
// 	new = ft_lstnew(wall);
// 	ft_lstadd_back(&game->walls, new);
// 	if (new->previous)
// 	{
// 		pwall = (t_wall *)new->previous->content;
// 		wall->start.x = pwall->end.x;
// 		wall->start.y = pwall->end.y;

// 		first = (t_wall *)game->walls->content;
// 		first->start.x = wall->end.x;
// 		first->start.y = wall->end.y;
// 	}
// 	// printf("wall ajoute en %f, %f\n", wall->coords.x, wall->coords.y);
// 	return ;
// }

// void	rm_last_wall(t_game *game)
// {
// 	t_list	*last, *previous;
// 	t_wall	*wall, *lastWall;

// 	if (!game->walls)
// 		return ;

// 	last = ft_lstlast(game->walls);
// 	previous = last->previous;

// 	if (previous)
// 		previous->next = NULL;
// 	else
// 		game->walls = NULL;
// 	ft_lstdelone(last, &free);

// 	if (game->walls)
// 	{
// 		lastWall = (t_wall *)ft_lstlast(game->walls)->content;
// 		wall = (t_wall *)game->walls->content;
// 		wall->start.x = lastWall->end.x;
// 		wall->start.y = lastWall->end.y;
// 	}

// 	return ;
// }
