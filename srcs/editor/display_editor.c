/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_editor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:22:45 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/07 12:41:58 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Affiche la partie gauche de l’éditeur. */
static void	left_part(t_game *game)
{
	SDL_Rect	rect;

	rect.x = 0;
	rect.y = 0;
	rect.h = game->window->h;
	rect.w = game->editor->plan.size.w;
	SDL_SetRenderDrawColor(game->window->renderPTR, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(game->window->renderPTR, &rect);

	display_grid(game);

	return ;
}

/* Affiche la partie droite de l’éditeur. */
static void	right_part(t_game *game)
{
	SDL_Rect	rect;

	rect.x = game->editor->plan.size.w + 1;
	rect.y = 0;
	rect.h = game->window->h;
	rect.w = game->editor->settings.w;

	SDL_SetRenderDrawColor(game->window->renderPTR, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(game->window->renderPTR, &rect);		// settings background

	display_separators(game);

	return ;
}

/* Affiche les textures des outils de l’éditeur. */
static void	display_tools_textures(t_game *game)
{
	t_editor	*editor = game->editor;
	SDL_Rect	dest;
	int			offset;

	offset = (120 * game->window->w) / 1920;
	dest.w = 100;
	dest.h = 100;
	dest.x = 1450;
	dest.y = 298;

	to_responsive(game->window, &dest);

	for (int i = 0; i < 4; i++)
	{
		if (i)
			dest.x += offset;

		if (editor->selected_tool == i)
			draw_texture(dest.x, dest.y, dest.w, dest.h, game->window, editor->buttons_textures[i + 4]);
		else
			draw_texture(dest.x, dest.y, dest.w, dest.h, game->window, editor->buttons_textures[i]);
	}

	return ;
}

/* Affiche l’éditeur complet. */
void	display_editor(t_game *game)
{
	left_part(game);
	display_editor_map(game);
	right_part(game);

	display_text_input(game, &game->editor->text_inputs);
	display_buttons(game->editor->buttons, game, -1);
	display_tools_textures(game);
	draw_texture_selector(game);

	display_properties(game);
	display_texture_selector_button(game);

	return ;
}
