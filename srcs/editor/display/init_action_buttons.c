/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_action_buttons.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:59:50 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/03 12:26:01 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static void	select_cursor(t_game *game)
{
	game->editor->selected_tool = 0;
	game->editor->properties.selected_property = 3;
}

static void	select_wall(t_game *game)
{
	game->editor->selected_tool = 1;
	game->editor->properties.selected_property = 1;
}

static void	select_slope(t_game *game)
{
	game->editor->selected_tool = 2;
}

/*	initaliser les boutons des propriétés	*/
void	init_action_buttons(t_game *game)
{
	SDL_Rect	dest;
	t_RGB		color = (t_RGB){0, 0, 0, 0};
	int			offset;
	void		*function[3] = {&select_cursor, &select_wall, &select_slope};

	offset = (145 * game->window->w) / 1920;
	dest.w = 100;
	dest.h = 100;
	dest.x = 1485;
	dest.y = 298;

	to_responsive(game->window, &dest);

	for (int i = 0; i < 3; i++)
	{
		if (i)
			dest.x = dest.x + offset;
		create_button(&game->editor->buttons, function[i], dest, color, color, NULL, NULL, -1);
	}

	return ;
}
