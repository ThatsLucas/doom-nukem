/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_text_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:30:46 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/07 16:09:51 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Ajoute un champ de saisie à l’éditeur. */
void	add_text_inputs(t_game *game, SDL_Rect coords, char *name, int page)
{
	t_text_input	*text;

	text = calloc(1, sizeof(t_text_input));
	if (!text)
		exit_game(game, "add_text_input");
	text->box = coords;
	text->name = name;
	text->page = page;

	ft_lstadd_back(&game->editor->text_inputs, ft_lstnew(text));

	return ;
}
