/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_settings_global_buttons.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:34:56 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/23 16:25:20 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* White label used by the global buttons */
static t_font	*button_label(t_game *game, char *label, int size)
{
	t_font	*text = calloc(1, sizeof(t_font));

	text->color = (SDL_Color){255, 255, 255, 255};
	text->size = size;
	create_text(text, game->window->renderPTR, label, "assets/fonts/MontserratBlack.ttf");
	return (text);
}

static void	add_global_button(t_game *game, void (*callback)(t_game *), SDL_Rect box,
				t_RGB colors[2], t_font *text)
{
	create_button(&game->editor->buttons, callback, box, colors[0], colors[1], text, text, -1);
}

/*	Boutons global des propriété (initialisation)	*/
void	init_settings_global_buttons(t_game *game)
{
	t_RGB	green[2] = {{0, 130, 32, 255}, {2, 168, 43, 255}};
	t_RGB	red[2] = {{170, 0, 0, 255}, {210, 0, 0, 255}};

	add_global_button(game, &update_grid_size, (SDL_Rect){.x = 1580, .y = 198, .w = 200, .h = 50},
		green, button_label(game, "update", 28));		// UPDATE button
	add_global_button(game, &save_editor_map, (SDL_Rect){.x = 1705, .y = 64, .w = 130, .h = 50},
		green, button_label(game, "save", 30));			// SAVE button
	add_global_button(game, &load_editor_map, (SDL_Rect){.x = 1525, .y = 64, .w = 130, .h = 50},
		green, button_label(game, "load", 30));			// LOAD button
	add_global_button(game, &clear_editor_plan, (SDL_Rect){.x = 1455, .y = 1015, .w = 450, .h = 50},
		red, button_label(game, "clear map", 30));		// clear map button
}
