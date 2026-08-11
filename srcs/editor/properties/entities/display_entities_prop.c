/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_entities_prop.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:36:33 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/15 16:38:47 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static void	draw_centered_text(t_game *game, char *txt, int x, int y)
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

	dst.x = x - (surface->w / 2);
	dst.y = y;
	dst.w = surface->w;
	dst.h = surface->h;
	SDL_FreeSurface(surface);
	to_responsive(game->window, &dst);

	SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dst);

	SDL_DestroyTexture(texture);
	return ;
}

void	display_entities_prop(t_game *game)
{
	display_buttons(game->editor->buttons_entities, game, -1);
	draw_centered_text(game, game->editor->entity_text, 1680, 480);
}
