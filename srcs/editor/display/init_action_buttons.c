/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_action_buttons.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:59:50 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:59:56 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Sélectionne l’outil curseur. */
static void	select_cursor(t_game *game)
{
	game->editor->selected_tool = 0;
	game->editor->properties.selected_property = 0;
}

/* Sélectionne l’outil mur. */
static void	select_wall(t_game *game)
{
	game->editor->selected_tool = 1;
	game->editor->properties.selected_property = 1;
}

/* Sélectionne l’outil pente. */
static void	select_slope(t_game *game)
{
	game->editor->selected_tool = 2;
	game->editor->properties.selected_property = 2;
}

/* Sélectionne l’outil entité. */
static void	select_entity(t_game *game)
{
	game->editor->selected_tool = 3;
	game->editor->properties.selected_property = 4;
	game->editor->entity_step = 0;
}

/* Crée les boutons des outils de l’éditeur. */
void	init_action_buttons(t_game *game)
{
	SDL_Rect	dest;
	t_RGB		color = (t_RGB){0, 0, 0, 0};
	int			offset;
	void		*function[4] = {&select_cursor, &select_wall, &select_slope, &select_entity};

	offset = (120 * game->window->w) / 1920;
	dest.w = 100;
	dest.h = 100;
	dest.x = 1450;
	dest.y = 298;

	to_responsive(game->window, &dest);

	for (int i = 0; i < 4; i++)
	{
		if (i)
			dest.x = dest.x + offset;
		create_button(&game->editor->buttons, function[i], dest, color, color, NULL, NULL, -1);
	}

	return ;
}
