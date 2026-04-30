/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_editor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:22:45 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/30 12:36:25 by aabouyaz         ###   ########.fr       */
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
	rect.w = game->window->w * 0.75;
	SDL_SetRenderDrawColor(game->window->renderPTR, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(game->window->renderPTR, &rect);

	display_grid(game);

	return ;
}

static void	right_part(t_game *game)
{
	SDL_Rect	rect;

	rect.x = game->window->w * 0.75;
	rect.y = 0;
	rect.h = game->window->h;
	rect.w = game->window->w * 0.25;

	SDL_SetRenderDrawColor(game->window->renderPTR, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(game->window->renderPTR, &rect);
	rect.x = game->window->w * 0.75 -200;
	rect.y = 20;
	rect.h = 30;
	rect.w = 100;
	SDL_SetTextInputRect(&rect);

	return ;
}

void	display_editor(t_game *game)
{
	left_part(game);
	right_part(game);

	// printf("%p == %p\n", game->editor->selected, game->editor->text_inputs->content);
	display_text_input(game, &game->editor->text_inputs);
	display_buttons(game->editor->buttons, game, -1);
	return ;
}
