/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_using.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:17:07 by edurance          #+#    #+#             */
/*   Updated: 2026/06/29 13:59:49 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

/* Called in events_handler to activate and desactivate flashlight */
void activate_flashlight(t_game *game)
{
	for (int i = 0; i < MAX_TOOLS; i++)
	{
		if (game->ply->inventory.tools[i].type == TOOL_FLASHLIGHT)
		{
			(game->ply->inventory.tools[i].using) = (game->ply->inventory.tools[i].using) ? 0 : 1;
		}
	}
}

/* Called in events_handler to use or not jetpack */
void activate_jetpack(t_game *game)
{
	for (int i = 0; i < MAX_TOOLS; i++)
	{
		if (game->ply->inventory.tools[i].type == TOOL_JETPACK)
		{
			if (game->ply->keys.space)
				game->ply->inventory.tools[i].using = 1;
			else
				game->ply->inventory.tools[i].using = 0;
		}
	}
}
