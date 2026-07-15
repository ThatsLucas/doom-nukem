/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sector_properties.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 12:04:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/08 14:30:00 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/*	Initialisation de la partie sector dans les propriétés	*/
void	init_sector_properties(t_game *game)
{
	SDL_Rect	box;

	box.w = 200;
	box.h = 100;

	box.x = 1472;
	box.y = 504;
	add_texture_selector_button(game, &game->editor->properties.sectors[0], 3, box);
	box.x = 1690;
	add_texture_selector_button(game, &game->editor->properties.sectors[1], 3, box);
	box.x = 1452;
	box.y = 840;
	add_texture_selector_button(game, &game->editor->properties.sectors[2], 3, box);

	box.w = 150;
	box.h = 50;
	box.x = 1686;
	box.y = 610;
	add_text_inputs(game, box, "sectors_light", 3);
	box.y = 665;
	add_text_inputs(game, box, "sectors_floor_z", 3);
	box.y = 719;
	add_text_inputs(game, box, "sectors_ceil_z", 3);

	box.w = 100;
	box.x = 1810;
	box.y = 828;
	add_text_inputs(game, box, "sectors_direction", 3);
	box.y = 883;
	add_text_inputs(game, box, "sectors_levelSize", 3);

	return ;
}
