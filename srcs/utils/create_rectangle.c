/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rectangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:46:22 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/05 11:46:34 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI.h"

void create_rectangle(SDL_Renderer *renderer, int x, int y, int w, int h, t_RGB rgb)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor( renderer, rgb.r, rgb.g, rgb.b, rgb.alphaValue );
	SDL_RenderFillRect( renderer, &rect );
}
