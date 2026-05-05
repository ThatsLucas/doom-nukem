/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_settings_global_inputs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:34:16 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 12:39:27 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

void	init_settings_global_inputs(t_game *game)
{
	SDL_Rect	box;

	box.w = 150;
	box.h = 50;
	box.y = 133;
	box.x = game->editor->plan.size.w + 65;
	add_text_inputs(game, box, "mapX");		// mapX
	box.x = game->editor->plan.size.w + 265;
	add_text_inputs(game, box, "mapY");		// mapY

	box.w = 300;
	box.h = 50;
	box.y = 23;
	box.x = game->editor->plan.size.w + 15;
	add_text_inputs(game, box, "mapName");	// map Name

	return ;
}
