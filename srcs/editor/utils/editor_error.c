/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:02:42 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/07 11:28:17 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

void	editor_error(t_game *game, char *txt)
{
	game->editor->error_text->size = 28;
	game->editor->error_text->color = (SDL_Color){255, 255, 255, 255};

	if (game->editor->error_text->texture)
		SDL_DestroyTexture(game->editor->error_text->texture);

	if (!txt)
	{
		SDL_DestroyTexture(game->editor->error_text->texture);
		ft_bzero(game->editor->error_text, sizeof(t_font));
		return ;
	}

	create_text(game->editor->error_text, game->window->renderPTR, txt, "assets/fonts/MontserratBlack.ttf");

	return ;
}

void	display_editor_error(t_game *game)
{
	SDL_Rect	background, text;

	background.w = 450;
	background.h = 50;
	background.x = 1455;
	background.y = 1015;

	SDL_SetRenderDrawColor(game->window->renderPTR, 200, 0, 0, SDL_ALPHA_OPAQUE);
	to_responsive(game->window, &background);
	SDL_RenderFillRect(game->window->renderPTR, &background);


	if (!game->editor->error_text->texture)
		return ;

	text.w = game->editor->error_text->w;
	text.h = game->editor->error_text->h;
	text.x = background.x + (background.w - game->editor->error_text->w) / 2;
	text.y = background.y + (background.h - game->editor->error_text->h) / 2;

	SDL_RenderCopy(game->window->renderPTR, game->editor->error_text->texture, NULL, &text);

	return ;
}
