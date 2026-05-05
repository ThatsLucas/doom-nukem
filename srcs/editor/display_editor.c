/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_editor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:22:45 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 12:57:30 by aabouyaz         ###   ########.fr       */
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

/* Display all the editor frame */
void	display_editor(t_game *game)
{
	left_part(game);
	right_part(game);

	display_text_input(game, &game->editor->text_inputs);
	display_buttons(game->editor->buttons, game, -1);
	return ;
}
