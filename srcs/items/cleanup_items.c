/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_items.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:41:50 by edurance          #+#    #+#             */
/*   Updated: 2026/04/09 10:45:47 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	cleanup_items(t_game *game)
{
	for (size_t i = 0; i < sizeof(game->items); i++)
	{
		if (game->items[i].texture)
		{
			SDL_DestroyTexture(game->items[i].texture);
			game->items[i].texture = NULL;
		}
	}
}
