/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:06:56 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/04 17:13:13 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/GUI.h"

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