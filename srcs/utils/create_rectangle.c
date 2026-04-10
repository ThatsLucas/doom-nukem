/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rectangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:46:22 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/10 10:38:15 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"

void create_rectangle(SDL_Renderer *renderer, t_coordinates coords, t_RGB rgb)
{
	SDL_Rect rect;

	rect.x = coords.x;
	rect.y = coords.y;
	rect.w = coords.w;
	rect.h = coords.h;
	SDL_SetRenderDrawColor( renderer, rgb.r, rgb.g, rgb.b, rgb.alphaValue );
	SDL_RenderFillRect( renderer, &rect );
}
