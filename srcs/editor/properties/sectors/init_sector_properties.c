/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sector_properties.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 12:04:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/08 15:04:13 by aabouyaz         ###   ########.fr       */
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
	box.x = 1582;
	box.y = 870;
	add_texture_selector_button(game, &game->editor->properties.sectors[2], 3, box);

	box.w = 150;
	box.h = 50;
	box.x = 1686;
	box.y = 634;
	add_text_inputs(game, box, "sectors_light", 3);
	box.y = 699;
	add_text_inputs(game, box, "sectors_z", 3);

	return ;
}
