/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_editor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:22:45 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/07 12:36:15 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

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

static void	display_tools_textures(t_game *game)
{
	t_editor	*editor = game->editor;
	SDL_Rect	dest;
	int			offset;

	offset = (145 * game->window->w) / 1920;
	dest.w = 100;
	dest.h = 100;
	dest.x = 1485;
	dest.y = 298;

	to_responsive(game->window, &dest);

	for (int i = 0; i < 3; i++)
	{
		if (i)
			dest.x += offset;

		if (editor->selected_tool == i)
			draw_texture(dest.x, dest.y, dest.w, dest.h, game->window, editor->buttons_textures[i + 3]);
		else
			draw_texture(dest.x, dest.y, dest.w, dest.h, game->window, editor->buttons_textures[i]);
	}

	return ;
}


/* Display all the editor frame */
void	display_editor(t_game *game)
{
	left_part(game);
	right_part(game);

	display_text_input(game, &game->editor->text_inputs);
	display_buttons(game->editor->buttons, game, -1);
	draw_texture_selector(game);
	display_editor_error(game);
	display_tools_textures(game);

	return ;
}
