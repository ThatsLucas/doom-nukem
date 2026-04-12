/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:06:56 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/05 11:48:33 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI.h"

int	SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius, t_RGB rgb)
{
	int offsetx, offsety, d;
	int status;

	offsetx = 0;
	offsety = radius;
	d = radius -1;
	status = 0;

	SDL_SetRenderDrawColor( renderer, rgb.r, rgb.g, rgb.b, rgb.alphaValue );


	SDL_Point	points[8];
	while (offsety >= offsetx) {

		points[0].x = x + offsetx; points[0].y = y + offsety;
		points[1].x = x + offsety; points[1].y = y + offsetx;
		points[2].x = x - offsetx; points[2].y = y + offsety;
		points[3].x = x - offsety; points[3].y = y + offsetx;
		points[4].x = x + offsetx; points[4].y = y - offsety;
		points[5].x = x + offsety; points[5].y = y - offsetx;
		points[6].x = x - offsetx; points[6].y = y - offsety;
		points[7].x = x - offsety; points[7].y = y - offsetx;

		SDL_RenderDrawPoints(renderer, points, 8);


		if (status < 0) {
			status = -1;
			break;
		}

		if (d >= 2*offsetx) {
			d -= 2*offsetx + 1;
			offsetx +=1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
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

		if (d >= 2*offsetx) {
			d -= 2*offsetx + 1;
			offsetx +=1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
}
