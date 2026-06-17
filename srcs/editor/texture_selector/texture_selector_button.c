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

static int	*get_tex_index_ptr(t_game *game, t_text_select_button *btn)
{
	t_editor_properties	*p = &game->editor->properties;
	t_map				*map = game->editor->map;

	if (btn->texture == &p->walls[0] && p->selected_wall >= 0 && p->selected_wall < map->num_walls)
		return (&map->walls[p->selected_wall].tex_upper);
	if (btn->texture == &p->walls[1] && p->selected_wall >= 0 && p->selected_wall < map->num_walls)
		return (&map->walls[p->selected_wall].tex_mid);
	if (btn->texture == &p->walls[2] && p->selected_wall >= 0 && p->selected_wall < map->num_walls)
		return (&map->walls[p->selected_wall].tex_lower);
	if (btn->texture == &p->sectors[0] && p->selected_sector >= 0 && p->selected_sector < map->num_sectors)
		return (&map->sectors[p->selected_sector].floor_tex);
	if (btn->texture == &p->sectors[1] && p->selected_sector >= 0 && p->selected_sector < map->num_sectors)
		return (&map->sectors[p->selected_sector].ceil_tex);
	if (btn->texture == &p->sectors[2] && p->selected_sector >= 0 && p->selected_sector < map->num_sectors)
		return (&map->sectors[p->selected_sector].sky_tex);
	return (NULL);
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
			create_texture_selector(game, btn->texture, get_tex_index_ptr(game, btn));
			return ;
		}

		current = current->next;
	}

	return ;
}

