/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_prop_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:33:47 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/29 23:25:04 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/*	Affichage du texte des propriétés	*/
void	draw_prop_text(t_game *game, char *txt, int x, int y)
{
	static SDL_Color	color = (SDL_Color){0, 0, 0, 255};
	SDL_Rect			dst;

	SDL_Surface *surface = TTF_RenderUTF8_Blended(game->editor->properties.font, txt, color);
	if (!surface)
	{
		ft_printf("TTF error: %s\n", TTF_GetError());
		return ;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface);

	dst.x = x;
	dst.y = y;
	dst.w = surface->w;
	dst.h = surface->h;
	SDL_FreeSurface(surface);
	to_responsive(game->window, &dst);

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dst);

	SDL_DestroyTexture(texture);
	return ;
}
