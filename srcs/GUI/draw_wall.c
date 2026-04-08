/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:15:48 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/08 12:31:58 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI.h"

void	draw_wall(t_game *game, t_vect2 a, t_vect2 b)
{
	SDL_RenderDrawLineF(game->window->renderPTR,
						to_pixelX(a.x, game), to_pixelY(a.y, game),
						to_pixelX(b.x, game), to_pixelY(b.y, game));

	return ;
}
