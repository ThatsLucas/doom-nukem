/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:15:35 by edurance          #+#    #+#             */
/*   Updated: 2026/05/08 10:41:37 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

/* Function to draw walls on the map -> red for walls (border) and brown for sectors portals */
void	draw_minimap_walls(t_game *game, SDL_Renderer *render)
{
	t_map	*map = game->map;

	float	cells_w = (float)MINI_W / MINI_CELLS;
	float	cells_h = (float)MINI_H / MINI_CELLS;
	float	ply_x = game->ply->pos.x;
	float	ply_y = game->ply->pos.y;

	float	offset_x = (MINI_W / 2.0f) - ply_x * cells_w;
	float	offset_y = (MINI_H / 2.0f) - ply_y * cells_h;

	// for each wall, get the vertices and draw them
	for (int i = 0; i < map->num_walls; i++)
	{
		t_wall	*wall = &map->walls[i];
		t_vect2	v1 = map->vertices[wall->v1];
		t_vect2	v2 = map->vertices[wall->v2];

		float	x1 = offset_x + v1.x * cells_w;
		float	y1 = offset_y + v1.y * cells_h;
		float	x2 = offset_x + v2.x * cells_w;
		float	y2 = offset_y + v2.y * cells_h;

		SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
		if (wall->next_sector == -1 || wall->alpha < 1.0f)
		{
			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
			draw_line_thick(render, x1, y1, x2, y2, 3);
		}
	}
}
