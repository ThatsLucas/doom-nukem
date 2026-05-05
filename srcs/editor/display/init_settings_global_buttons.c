/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_settings_global_buttons.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:34:56 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 13:38:23 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

void	init_settings_global_buttons(t_game *game)
{
	SDL_Rect	box;
	t_font		*text = calloc(1, sizeof(t_font));
	t_RGB		btn_color = {0, 130, 32, 255};
	t_RGB		hov_color = {2, 168, 43, 255};

	text->color = (SDL_Color){255, 255, 255, 255};
	text->size = 30;
	create_text(text, game->window->renderPTR, "update", "assets/fonts/MontserratBlack.ttf");

	box.w = 250;
	box.h = 50;
	box.x = 1555;
	box.y = 198;
	create_button(&game->editor->buttons, &update_grid_size, box, btn_color, hov_color, text, text, -1);	// UPDATE button

	create_text(text, game->window->renderPTR, "save", "assets/fonts/MontserratBlack.ttf");

	box.w = 130;
	box.h = 50;
	box.x = 1775;
	box.y = 23;

	create_button(&game->editor->buttons, NULL, box, btn_color, hov_color, text, text, -1);					// SAVE button

	return ;
}
