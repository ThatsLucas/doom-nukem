/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_properties.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:13:26 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/07 17:20:47 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

void	display_properties(t_game *game)
{
	switch (game->editor->properties.selected_property)
	{
	case 0:
		return ;
	
	case 1:
		display_walls_property(game);
		return ;
	}

	return ;
}

void	init_properties(t_game *game)
{
	t_editor	*editor = game->editor;

	editor->properties.font = TTF_OpenFont("assets/fonts/Inter_28pt-Regular.ttf", 30);
	if (!editor->properties.font)
		exit_game(game, "init_properties editor");
	init_walls_properties(game);

	return ;
}
