/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:53:22 by edurance          #+#    #+#             */
/*   Updated: 2026/05/07 15:55:59 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"

void	draw_player_minimap(SDL_Renderer *render, t_game *game, int size, t_RGB color)
{
	SDL_Vertex	points[3];
	float		local_x, local_y;
	t_ply		*ply = game->ply;
	float		posx = MINI_W / 2.0f;
	float		posy = MINI_H / 2.0f;

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

	SDL_RenderGeometry(render, NULL, points, 3, NULL, 0);
}
