/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_slope_properties.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 11:36:31 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/17 11:46:52 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Crée les champs des propriétés des pentes. */
void	init_slope_properties(t_game *game)
{
	SDL_Rect	box;

	box.w = 150;
	box.h = 50;
	box.x = 1714;
	box.y = 570;
	add_text_inputs(game, box, "ceil_intensity", 2);
	box.y = 655;
	add_text_inputs(game, box, "floor_intensity", 2);

	return ;
}
