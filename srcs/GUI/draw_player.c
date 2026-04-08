/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:03:18 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/08 13:00:15 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI.h"
#include "Game.h"

static SDL_Color	RGBtoSDLColor(t_RGB color)
{
	SDL_Color	res;

	res.a = color.alphaValue;
	res.r = color.r;
	res.g = color.g;
	res.b = color.b;

	return (res);
}

void	draw_player(SDL_Renderer *renderer, t_game *game, int size, t_RGB color)
{
	SDL_Vertex	points[3];
	float		local_x, local_y;
	t_ply		*ply = game->ply;
	float		posx = to_pixelX(ply->pos.x, game);
	float		posy = to_pixelY(ply->pos.y, game);

	// Sommet (haut)
	local_x = 0;
	local_y = size * 1.0f;
	points[0].position.x = -local_x * ply->dir.y + local_y * ply->dir.x + posx;
	points[0].position.y = local_x * ply->dir.x + local_y * ply->dir.y + posy;
	points[0].color = RGBtoSDLColor(color);

	// Bas gauche
	local_x = size / 1.5f;
	local_y = -size / 2.0f;
	points[1].position.x = -local_x * ply->dir.y + local_y * ply->dir.x + posx;
	points[1].position.y = local_x * ply->dir.x + local_y * ply->dir.y + posy;
	points[1].color = RGBtoSDLColor(color);

	// Bas droite
	local_x = -size / 1.5f;
	local_y = -size / 2.0f;
	points[2].position.x = -local_x * ply->dir.y + local_y * ply->dir.x + posx;
	points[2].position.y = local_x * ply->dir.x + local_y * ply->dir.y + posy;
	points[2].color = RGBtoSDLColor(color);

	SDL_RenderGeometry(renderer, NULL, points, 3, NULL, 0);
}
