/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit_editor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:06:03 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/30 12:53:03 by aabouyaz         ###   ########.fr       */
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

	SDL_Rect box;
	box.w = 100;
	box.h = 40;
	box.y = 20;
	box.x = game->window->w * 0.75 + 10;
	add_text_inputs(game, box, "mapX");
	box.x = box.x + box.w + 20;
	add_text_inputs(game, box, "mapY");
	box.w = 200;
	box.x = game->window->w - box.w - 20;

	t_RGB btn_color;
	btn_color.r = 125, btn_color.g = 75; btn_color.b = 25; btn_color.alphaValue = 255;

	t_font txt;

	txt.size = 15;
	create_text(&txt, game->window->renderPTR, "UPDATE", "assets/fonts/MontserratBlack.ttf");
	create_button(&game->editor->buttons, &update_grid_size, box, btn_color, btn_color, &txt, &txt, -1);


	return ;
}

void	exit_editor(t_game *game)
{
	TTF_CloseFont(game->editor->font); 
	ft_lstclear(&game->editor->text_inputs, free);
	free(game->editor);

	return ;
}
