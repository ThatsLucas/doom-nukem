/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_settings_global_inputs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:34:16 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 13:09:34 by aabouyaz         ###   ########.fr       */
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
	box.x = 1505;
	add_text_inputs(game, box, "mapX");		// mapX
	box.x = 1705;
	add_text_inputs(game, box, "mapY");		// mapY

	box.w = 300;
	box.h = 50;
	box.y = 23;
	box.x = 1455;
	add_text_inputs(game, box, "mapName");	// map Name

	return ;
}
