/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_selected_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:55:41 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/27 21:03:55 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

void	get_selected_input(t_editor *editor, t_list **lst, int x, int y)
{
	t_list			*current = *lst;
	t_text_input	*input = NULL;

	while (current)
	{
		input = (t_text_input *)current->content;
		if (x >= input->box.x && x <= input->box.x + input->box.w
			&& y >= input->box.y && y <= input->box.y + input->box.h)
		{
			editor->selected = input;
			return ;
		}

		current = current->next;
	}

	editor->selected = NULL;

	return ;
}
