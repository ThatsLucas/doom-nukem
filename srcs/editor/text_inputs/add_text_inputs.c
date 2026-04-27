/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_text_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:30:46 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/27 18:37:11 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

void	add_text_inputs(t_game *game, SDL_Rect coords)
{
	t_text_input	*text;

	text = calloc(1, sizeof(t_text_input));
	if (!text)
		exit_game(game, "add_text_input");
	text->box = coords;

	ft_lstadd_back(&game->editor->text_inputs, ft_lstnew(text));

	return ;
}
