/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit_editor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:06:03 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/27 21:20:07 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

void	init_editor(t_game *game)
{
	game->editor = calloc(1, sizeof(t_editor));
	if (!game->editor)
		exit_game(game, "init editor");
	game->editor->font = TTF_OpenFont("assets/fonts/MontserratBlack.ttf", 25);
	if (!game->editor->font)
		exit_game(game, "display_editor font");

	SDL_Rect box;
	box.w = 200;
	box.h = 40;
	box.x = game->window->w * 0.75 + (game->window->w * 0.25 - box.w - 10);
	box.y = 20;
	add_text_inputs(game, box);

	box.x = game->window->w * 0.75 + 10;
	add_text_inputs(game, box);

	return ;
}

void	exit_editor(t_game *game)
{
	TTF_CloseFont(game->editor->font); 
	ft_lstclear(&game->editor->text_inputs, free);
	free(game->editor);

	return ;
}
