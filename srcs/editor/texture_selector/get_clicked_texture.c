/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clicked_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:36:50 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/08 15:00:53 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Vérifie si le point se trouve dans le rectangle. */
static int	is_in_box(int x, int y, SDL_Rect *rect)
{
	if (x <= rect->x + rect->w && x > rect->x && y <= rect->y + rect->h && y > rect->y)
		return (1);

	return (0);
}

/* Vérifie si le curseur se trouve sur une texture. */
static int	is_on_texture(int x, int y)
{
	int	count = 0;

	for (int i = 0; i < 5; i++)
	{
		if (x > i * 120 && x < i * 120 + 100)
			count ++;
	}

	for (int i = 0; i < 3; i++)
	{
		if (y > i * 120 && y < i * 120 + 100)
			count++;
	}

	if (count == 2)
		return (1);
	return (0);
}

/* Enregistre la texture sélectionnée dans la variable destinataire. */
static void	set_selected_texture(t_game *game, int selected)
{
	if (selected == game->editor->textures->num_textures)
	{
		*game->editor->texture_selector.variable_to_set = NULL;
		if (game->editor->texture_selector.index_to_set)
			*game->editor->texture_selector.index_to_set = -1;
	}
	else
	{
		*game->editor->texture_selector.variable_to_set = game->editor->textures->textures[selected];
		if (game->editor->texture_selector.index_to_set)
			*game->editor->texture_selector.index_to_set = selected;
	}
	game->editor->texture_selector.display = 0;
	game->editor->texture_selector.variable_to_set = NULL;
	game->editor->texture_selector.index_to_set = NULL;
}

/* Sélectionne la texture cliquée. */
void	get_clicked_texture(t_game *game, int x, int y)
{
	SDL_Rect	box = { .x = 710, .y = 555, .w = 580, .h = 340};
	int			selected;

	if (!game->editor->texture_selector.variable_to_set)
		return ;

	x = (x * 1920 / game->window->w);
	y = (y * 1080 / game->window->h);
	if (!is_in_box(x, y, &box))
		return ;
	x -= box.x;
	y -= box.y;

	if (!is_on_texture(x, y))
		return ;

	selected = (y / 120) * 5 + (x / 120) + game->editor->texture_selector.page * 15;
	if (selected > game->editor->textures->num_textures)
		return ;
	set_selected_texture(game, selected);

	return ;
}
