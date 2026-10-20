/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_selected_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:55:41 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/08 14:46:06 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Récupère le champ de saisie sélectionné. */
void	get_selected_input(t_game *game, t_list **lst, int x, int y)
{
	t_editor		*editor = game->editor;
	t_list			*current = *lst;
	t_text_input	*input = NULL;
	SDL_Rect		box;

	while (current)
	{
		input = (t_text_input *)current->content;

		if (input->page > 0 && input->page != editor->properties.selected_property)
		{
			current = current->next;
			continue ;
		}
		box = input->box;
		to_responsive(game->window, &box);
		if (x >= box.x && x <= box.x + box.w && y >= box.y && y <= box.y + box.h)
		{
			editor->selected = input;
			return ;
		}

		current = current->next;
	}

	editor->selected = NULL;

	return ;
}
