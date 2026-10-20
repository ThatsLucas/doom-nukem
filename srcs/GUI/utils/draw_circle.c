/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:06:56 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/10 10:38:20 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"

/* One step of the midpoint circle algorithm */
static void	circle_step(int *d, int *offsetx, int *offsety, int radius)
{
	if (*d >= 2 * *offsetx) {
		*d -= 2 * *offsetx + 1;
		*offsetx += 1;
	}
	else if (*d < 2 * (radius - *offsety)) {
		*d += 2 * *offsety - 1;
		*offsety -= 1;
	}
	else {
		*d += 2 * (*offsety - *offsetx - 1);
		*offsety -= 1;
		*offsetx += 1;
	}
}

/* The 8 symmetric points of the circle for this offset */
static void	draw_circle_points(SDL_Renderer *renderer, int x, int y, int offsetx, int offsety)
{
	SDL_Point	points[8];

	points[0].x = x + offsetx; points[0].y = y + offsety;
	points[1].x = x + offsety; points[1].y = y + offsetx;
	points[2].x = x - offsetx; points[2].y = y + offsety;
	points[3].x = x - offsety; points[3].y = y + offsetx;
	points[4].x = x + offsetx; points[4].y = y - offsety;
	points[5].x = x + offsety; points[5].y = y - offsetx;
	points[6].x = x - offsetx; points[6].y = y - offsety;
	points[7].x = x - offsety; points[7].y = y - offsetx;

	SDL_RenderDrawPoints(renderer, points, 8);
}

int	SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius, t_RGB rgb)
{
	int offsetx, offsety, d;

	offsetx = 0;
	offsety = radius;
	d = radius -1;

	SDL_SetRenderDrawColor( renderer, rgb.r, rgb.g, rgb.b, rgb.alphaValue );

	while (offsety >= offsetx) {
		draw_circle_points(renderer, x, y, offsetx, offsety);
		circle_step(&d, &offsetx, &offsety, radius);
	}

	return 0;
}

int	SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius, t_RGB rgb)
{
	int offsetx, offsety, d;
	int status;

	offsetx = 0;
	offsety = radius;
	d = radius -1;
	status = 0;

	SDL_SetRenderDrawColor( renderer, rgb.r, rgb.g, rgb.b, rgb.alphaValue );

	while (offsety >= offsetx) {

		status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
									 x + offsety, y + offsetx);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
									 x + offsetx, y + offsety);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
									 x + offsetx, y - offsety);
		status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
									 x + offsety, y - offsetx);

		if (status < 0) {
			status = -1;
			break;
		}
		circle_step(&d, &offsetx, &offsety, radius);
	}

	return status;
}
