/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls_properties.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:24:44 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/29 23:23:45 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/*	Initialisation de la partie murs dans les propriétés	*/
void	init_walls_properties(t_game *game)
{
	SDL_Rect	box;

	box.w = 200;
	box.h = 100;

	box.x = 1690;
	box.y = 489;
	add_texture_selector_button(game, game->editor->properties.walls[0], 1, box);
	box.y = 604;
	add_texture_selector_button(game, game->editor->properties.walls[1], 1, box);
	box.y = 719;
	add_texture_selector_button(game, game->editor->properties.walls[2], 1, box);

	box.w = 150;
	box.h = 50;
	box.x = 1715;
	box.y = 879;
	add_text_inputs(game, box, "walls_alpha", 1);

	return ;
}
