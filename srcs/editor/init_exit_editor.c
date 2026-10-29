/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit_editor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:06:03 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:16:18 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Initialise les boutons et les champs de saisie de l’éditeur. */
static void	init_buttons_inputs(t_game *game)
{
	init_settings_global_buttons(game);
	init_settings_global_inputs(game);

	return ;
}

/* Initialise l’éditeur. */
void	init_editor(t_game *game)
{
	game->editor = calloc(1, sizeof(t_editor));
	if (!game->editor)
		exit_game(game, "init editor");
	game->editor->font = TTF_OpenFont("assets/fonts/MontserratBlack.ttf", 24);
	if (!game->editor->font)
		exit_game(game, "display_editor font");
	init_editor_cache(game);
	init_editor_map(game);

	game->editor->map->mapSize.x = 12;	game->editor->map->mapSize.y = 8;	// default size
	game->editor->plan.size = (t_size2){game->window->w * 0.75, game->window->h};
	update_grid_size(game);
	game->editor->settings = (t_size2){game->window->w * 0.25, game->window->h};

	init_buttons_inputs(game);
	init_action_buttons(game);
	init_properties(game);

	game->editor->error_text = calloc(1, sizeof(t_font));
	if (!game->editor->error_text)
		exit_game(game, "editor: cant calloc error_text");

	return ;
}

/* Libère les libellés alloués des boutons de l’éditeur, puis les boutons. */
static void	free_editor_buttons(t_buttons *buttons)
{
	for (t_buttons *b = buttons; b; b = b->next)
	{
		if (b->text)
		{
			destroy_text_texture(b->text);
			free(b->text);
		}
	}
	free_buttons(buttons);
}

/* Libère l’éditeur et revient au menu. */
void	exit_editor(t_game *game)
{
	if (!game->editor)
		return ;
	TTF_CloseFont(game->editor->font); 
	ft_lstclear(&game->editor->text_inputs, free);
	ft_lstclear(&game->editor->texture_selector_buttons, free);
	free_editor_buttons(game->editor->buttons);
	free_editor_buttons(game->editor->buttons_entities);
	if (game->editor->textures)
	{
		free(game->editor->textures->png);
		free(game->editor->textures->textures);
	}
	TTF_CloseFont(game->editor->properties.font);
	free(game->editor->error_text);
	free(game->editor->textures);

	free_map(game->editor->map);

	free(game->editor);

	return ;
}
