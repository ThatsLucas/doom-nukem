/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:03:18 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/10 10:38:25 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"
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

void	draw_player(SDL_Renderer *renderer, t_ply *ply, int size, t_RGB color)
{
	SDL_Vertex	points[3];
	float		local_x, local_y;

	// Sommet (haut)
	local_x = 0;
	local_y = size * 1.0f;
	points[0].position.x = -local_x * ply->dir_y + local_y * ply->dir_x + ply->pos_x;
	points[0].position.y =  local_x * ply->dir_x + local_y * ply->dir_y + ply->pos_y;
	points[0].color = RGBtoSDLColor(color);

	// Bas gauche
	local_x = size / 1.5f;
	local_y = -size / 2.0f;
	points[1].position.x = -local_x * ply->dir_y + local_y * ply->dir_x + ply->pos_x;
	points[1].position.y =  local_x * ply->dir_x + local_y * ply->dir_y + ply->pos_y;
	points[1].color = RGBtoSDLColor(color);

	// Bas droite
	local_x = -size / 1.5f;
	local_y = -size / 2.0f;
	points[2].position.x = -local_x * ply->dir_y + local_y * ply->dir_x + ply->pos_x;
	points[2].position.y =  local_x * ply->dir_x + local_y * ply->dir_y + ply->pos_y;
	points[2].color = RGBtoSDLColor(color);

	SDL_RenderGeometry(renderer, NULL, points, 3, NULL, 0);
}