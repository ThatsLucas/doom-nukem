/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_settings_global_buttons.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:34:56 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/29 22:57:29 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/*	Boutons global des propriété (initialisation)	*/
void	init_settings_global_buttons(t_game *game)
{
	SDL_Rect	box;
	t_font		*name_text = calloc(1, sizeof(t_font));
	t_font		*update_text = calloc(1, sizeof(t_font));
	t_RGB		btn_color = {0, 130, 32, 255};
	t_RGB		hov_color = {2, 168, 43, 255};

	name_text->color = (SDL_Color){255, 255, 255, 255};
	name_text->size = 30;
	create_text(name_text, game->window->renderPTR, "update", "assets/fonts/MontserratBlack.ttf");

	box.w = 250;
	box.h = 50;
	box.x = 1555;
	box.y = 198;
	create_button(&game->editor->buttons, &update_grid_size, box, btn_color, hov_color, name_text, name_text, -1);	// UPDATE button

	update_text->color = (SDL_Color){255, 255, 255, 255};
	update_text->size = 30;

	create_text(update_text, game->window->renderPTR, "save", "assets/fonts/MontserratBlack.ttf");

	box.w = 130;
	box.h = 50;
	box.x = 1775;
	box.y = 23;

	create_button(&game->editor->buttons, NULL, box, btn_color, hov_color, update_text, update_text, -1);					// SAVE button

	return ;
}
