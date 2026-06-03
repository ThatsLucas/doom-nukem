/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_settings_global_buttons.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:34:56 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/03 09:28:43 by aabouyaz         ###   ########.fr       */
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
	t_font		*clear_text = calloc(1, sizeof(t_font));
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

	clear_text->color = (SDL_Color){255, 255, 255, 255};
	clear_text->size = 30;
	create_text(clear_text, game->window->renderPTR, "clear map", "assets/fonts/MontserratBlack.ttf");

	box.w = 450;
	box.h = 50;
	box.x = 1455;
	box.y = 1015;
	btn_color = (t_RGB){170, 0, 0, 255};
	hov_color = (t_RGB){210, 0, 0, 255};
	create_button(&game->editor->buttons, &clear_editor_plan, box, btn_color, hov_color, clear_text, clear_text, -1);					// SAVE button

	return ;
}
