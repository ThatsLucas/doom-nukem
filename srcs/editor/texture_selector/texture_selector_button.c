/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_selector_button.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:50:11 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/08 15:04:50 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

void	add_texture_selector_button(t_game *game, SDL_Texture **text, int page, SDL_Rect box)
{
	t_text_select_button	*new;

	new = calloc(1, sizeof(t_text_select_button));
	if (!new)
		exit_game(game, "Can't create a texture selector button");

	new->box = box;
	new->page = page;
	new->texture = text;

	ft_lstadd_back(&game->editor->texture_selector_buttons, ft_lstnew(new));

	return ;
}

void	display_texture_selector_button(t_game *game)
{
	t_list					*current = game->editor->texture_selector_buttons;
	t_text_select_button	*btn = NULL;
	SDL_Rect				rect;

	SDL_SetRenderDrawColor(game->window->renderPTR, 0, 0, 0, 255);

	while (current)
	{
		btn = (t_text_select_button *)current->content;
		if (btn->page > 0 && btn->page != game->editor->properties.selected_property)
		{
			current = current->next;
			continue ;
		}

		rect = btn->box;
		to_responsive(game->window, &rect);
		if (btn->texture && *btn->texture)
			draw_texture_rounded(rect.x, rect.y, rect.w, rect.h, game->window, *btn->texture);
		else
			SDL_RenderDrawRect(game->window->renderPTR, &rect);

		current = current->next;
	}

	return ;
}

void	get_clicked_texture_button(t_game *game, int x, int y)
{
	t_list					*current = game->editor->texture_selector_buttons;
	t_text_select_button	*btn = NULL;
	SDL_Rect				rect;

	while (current)
	{
		btn = (t_text_select_button *)current->content;

		if (btn->page > 0 && btn->page != game->editor->properties.selected_property)
		{
			current = current->next;
			continue ;
		}

		rect = btn->box;
		to_responsive(game->window, &rect);

		if (x <= rect.x + rect.w && x > rect.x && y <= rect.y + rect.h && y > rect.y)
		{
			create_texture_selector(game, btn->texture);
			return ;
		}

		current = current->next;
	}

	return ;
}

