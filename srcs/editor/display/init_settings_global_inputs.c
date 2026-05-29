/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_settings_global_inputs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:34:16 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/29 22:58:34 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/*	Initalisation des inputs dans les propriétés	*/
void	init_settings_global_inputs(t_game *game)
{
	SDL_Rect	box;

	box.w = 150;
	box.h = 50;
	box.y = 133;
	box.x = 1505;
	add_text_inputs(game, box, "mapX", -1);		// mapX
	box.x = 1705;
	add_text_inputs(game, box, "mapY", -1);		// mapY

	box.w = 300;
	box.h = 50;
	box.y = 23;
	box.x = 1455;
	add_text_inputs(game, box, "mapName", -1);	// map Name

	return ;
}
