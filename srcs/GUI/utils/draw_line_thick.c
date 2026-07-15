/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_thick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:32:37 by edurance          #+#    #+#             */
/*   Updated: 2026/05/07 12:32:44 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	draw_line_thick(SDL_Renderer *ren, float x1, float y1, float x2, float y2, int thickness)
{
	float	dx = x2 - x1;
	float	dy = y2 - y1;
	float	len = sqrtf(dx * dx + dy * dy);
	float	nx = -dy / len * 0.5f;  // normale perpendiculaire
	float	ny =  dx / len * 0.5f;

	for (int i = -(thickness / 2); i <= thickness / 2; i++)
	{
		SDL_RenderDrawLineF(ren,x1 + nx * i, y1 + ny * i, x2 + nx * i, y2 + ny * i);
	}
}
