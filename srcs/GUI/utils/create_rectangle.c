/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rectangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:46:22 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/12 19:13:40 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI.h"

void create_rectangle(SDL_Renderer *renderer, SDL_Rect coords, t_RGB rgb)
{
	SDL_SetRenderDrawColor( renderer, rgb.r, rgb.g, rgb.b, rgb.alphaValue );
	SDL_SetRenderDrawBlendMode(renderer,  SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect( renderer, &coords );
}
