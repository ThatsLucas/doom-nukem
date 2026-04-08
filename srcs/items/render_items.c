/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:40:12 by edurance          #+#    #+#             */
/*   Updated: 2026/04/08 17:40:19 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	render_items(t_game *game)
{
	for (size_t i = 0; i < 10; i++)
	{
		t_ground_item	*item = &game->items[i];
		if (item->pos_x < 0)
			continue ;

		if (!game->items->texture)
			continue;
		
		SDL_Rect dest = {
			(int)item->pos_x,
			(int)item->pos_y,
			item->w,
			item->h
		};
		SDL_RenderCopy(game->window->renderPTR, item->texture, NULL, &dest);
	}
}
