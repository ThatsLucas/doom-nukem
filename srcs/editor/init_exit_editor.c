/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit_editor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:06:03 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/02 13:50:01 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

static void	update_grid_size(t_game *game)
{
	t_list			*current = game->editor->text_inputs;
	t_text_input	*input;

	while (current)
	{
		input = (t_text_input *)current->content;

		if (!ft_strcmp("mapX", input->name) && ft_atoi(input->text) > 0)
			game->mapSize[0] = ft_atoi(input->text);
		else if (!ft_strcmp("mapY", input->name) && ft_atoi(input->text) > 0)
			game->mapSize[1] = ft_atoi(input->text);

		current = current->next;
	}

	return ;
}

void	init_editor(t_game *game)
{
	game->editor = calloc(1, sizeof(t_editor));
	if (!game->editor)
		exit_game(game, "init editor");
	game->editor->font = TTF_OpenFont("assets/fonts/MontserratBlack.ttf", 25);
	if (!game->editor->font)
		exit_game(game, "display_editor font");

	game->editor->plan = (t_size2){game->window->w * 0.75, game->window->h};
	game->editor->settings = (t_size2){game->window->w * 0.25, game->window->h};

	SDL_Rect box;
	box.w = 100;
	box.h = 40;
	box.y = 20;
	box.x = game->editor->plan.w + 10;
	add_text_inputs(game, box, "mapX");
	box.x = box.x + box.w + 20;
	add_text_inputs(game, box, "mapY");
	box.w = 200;
	box.x = game->window->w - box.w - 20;

	SDL_Color	red = {221, 21, 0, 255};
	t_font *text_hover = calloc(1, sizeof(t_font));
	text_hover->color = red;
	text_hover->size = 30;

	create_text(text_hover, game->window->renderPTR, "update", "assets/fonts/MontserratBlack.ttf");

	t_RGB btn_color = {125, 75, 25, 255};
	t_RGB hov_color = {15, 175, 25, 255};
	create_button(&game->editor->buttons, &update_grid_size, box, btn_color, hov_color, text_hover, text_hover, -1);

	return ;
}

void	exit_editor(t_game *game)
{
	TTF_CloseFont(game->editor->font); 
	ft_lstclear(&game->editor->text_inputs, free);
	free_buttons(game->editor->buttons);
	free(game->editor);

	return ;
}
