/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit_editor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:06:03 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/08 10:30:51 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

static void	init_buttons_inputs(t_game *game)
{
	init_settings_global_buttons(game);
	init_settings_global_inputs(game);

	return ;
}

void	init_editor(t_game *game)
{
	game->editor = calloc(1, sizeof(t_editor));
	if (!game->editor)
		exit_game(game, "init editor");
	game->editor->font = TTF_OpenFont("assets/fonts/MontserratBlack.ttf", 24);
	if (!game->editor->font)
		exit_game(game, "display_editor font");
	init_editor_cache(game);

	game->mapSize[0] = 12;	game->mapSize[1] = 8;	// default size
	game->editor->plan.size = (t_size2){game->window->w * 0.75, game->window->h};
	update_grid_size(game);
	game->editor->settings = (t_size2){game->window->w * 0.25, game->window->h};

	init_buttons_inputs(game);
	init_action_buttons(game);
	init_properties(game);

	game->editor->error_text = calloc(1, sizeof(t_font));
	if (!game->editor->error_text)
		exit_game(game, "editor: cant calloc error_text");
	init_editor_map(game);

	return ;
}

void	exit_editor(t_game *game)
{
	TTF_CloseFont(game->editor->font); 
	ft_lstclear(&game->editor->text_inputs, free);
	free_buttons(game->editor->buttons);
	if (game->editor->textures)
	{
		free(game->editor->textures->png);
	}
	TTF_CloseFont(game->editor->properties.font);
	free(game->editor->error_text);
	free(game->editor->textures);

	free(game->editor->map->sectors);
	free(game->editor->map->textures);
	free(game->editor->map->vertices);
	free(game->editor->map->walls);
	free(game->editor->map);

	free(game->editor);

	return ;
}
