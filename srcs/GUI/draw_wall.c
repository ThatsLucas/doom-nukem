/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:15:48 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/09 12:05:41 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI.h"

void	draw_wall(t_game *game, t_vect2 a, t_vect2 b, t_RGB color)
{
	SDL_SetRenderDrawColor(	game->window->renderPTR,
							color.r, color.g, color.b,
							color.alphaValue);
	SDL_RenderDrawLineF(game->window->renderPTR,
						to_pixelX(a.x, game), to_pixelY(a.y, game),
						to_pixelX(b.x, game), to_pixelY(b.y, game));

	return ;
}

void	draw_walls(t_game *game, t_RGB rgb)
{
	t_list	*current = game->walls;
	t_wall	*wall, *next_wall;
	int		elements = ft_lstsize(game->walls);

	if (elements <= 1)
		return ;

	while (current)
	{
		wall = (t_wall *)current->content;
		if (current->next)
			next_wall = (t_wall *)current->next->content;
		else
			next_wall = (t_wall *)game->walls->content;
		draw_wall(game, wall->coords, next_wall->coords, rgb);
		current = current->next;
	}

	return ;
}
