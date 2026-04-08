/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/08 16:52:24 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI.h"
#include "Game.h"
#include "Events.h"
#include "parser/PNG.h"

int main(void)
{

	process_png("assets/png/doom_nukem.png");

	t_game	*game;

	game = init_game();
	if (!game)
		return (1);

	t_RGB rgb;
	rgb.r = 51;
	rgb.g = 153;
	rgb.b = 255;
	rgb.alphaValue = 255;

	// t_coordinates coords;
	// coords.x = 200;
	// coords.y = 200;
	// coords.w = 150;
	// coords.h = 80;

	// t_RGB buttoncolor;
	// buttoncolor.r = 0;
	// buttoncolor.g = 60;
	// buttoncolor.b = 255;
	// buttoncolor.alphaValue = 255;

	// t_RGB hoverColor;
	// hoverColor.r = 90;
	// hoverColor.g = 60;
	// hoverColor.b = 150;
	// hoverColor.alphaValue = 255;

	// create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);
	// coords.x = 200;
	// coords.y = 300;
	// create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);
	// coords.x = 200;
	// coords.y = 400;
	// create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);

	game->ply->pos.x = 3;
	game->ply->pos.y = 2;
	game->ply->dir.x = 1.0f;
	game->ply->dir.y = 0.0f;
	ft_bzero(&game->ply->keys, sizeof(t_keys));

	game->mapSize[0] = 7;	game->mapSize[1] = 4;
	t_vect2	p[7];
	int		elements = sizeof(p) / sizeof(t_vect2);
	t_vect2	intersection;
	float	min_t;

	p[0].x = 2.0f;	p[0].y = 0.5f;
	p[1].x = 4.5f;	p[1].y = 0.2f;
	p[2].x = 6.0f;	p[2].y = 1.4f;
	p[3].x = 4.2f;	p[3].y = 2.5f;
	p[4].x = 5.5f;	p[4].y = 2.9f;
	p[5].x = 2.0f;	p[5].y = 3.5f;
	p[6].x = 0.7f;	p[6].y = 2.4f;

	while (1)
	{
		events_handler(game);

		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 120, 52, 50, 255);
		SDL_RenderClear(game->window->renderPTR);

		display_buttons(game->window->buttonList, game->window->renderPTR);
		// Creation du renderer (de la frame)
		// SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);

		SDL_SetRenderDrawColor(game->window->renderPTR, 0, 0, 255, 255);
		t_ray	ray;

		ray.plane.x = game->ply->dir.y * -1 * 0.57;
		ray.plane.y = game->ply->dir.x * 0.57;
		for (int i = 0; i < game->screenSize[0]; i++)
		{

			ray.camera_x = 2 * i / (float)game->screenSize[0] - 1.0f;
			ray.ray_dir.x = game->ply->dir.x + ray.plane.x * ray.camera_x;
			ray.ray_dir.y = game->ply->dir.y + ray.plane.y * ray.camera_x;

			min_t = INT_MAX;
			for (int i = 0; i < elements; i++)
			{
				if (i == elements - 1)
				{
					draw_wall(game, p[i], p[0], rgb);
					inter_point(game->ply->pos, ray.ray_dir, p[i], edge(p[i], p[0]), &intersection, &min_t);
				}
				else
				{
					draw_wall(game, p[i], p[i + 1], rgb);
					inter_point(game->ply->pos, ray.ray_dir, p[i], edge(p[i], p[i + 1]), &intersection, &min_t);
				}
			}
			if (intersection.x != -1)
				SDL_RenderDrawLineF(game->window->renderPTR, to_pixelX(game->ply->pos.x,game), to_pixelY(game->ply->pos.y, game), to_pixelX(intersection.x, game), to_pixelY(intersection.y, game));
			intersection.x = -1;
		}

		draw_player(game->window->renderPTR, game, 20, rgb);

		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
	}

	exit_game(game, NULL);

	return 0;
}
