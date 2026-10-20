/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:54:02 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/06 16:11:47 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Recentre la vue sur la grille et ajuste le zoom. */
void	fit_grid_view(t_game *game)
{
	t_plan	*plan = &game->editor->plan;
	float	fit_x;
	float	fit_y;

	fit_x = plan->size.w / game->editor->map->mapSize.x;
	fit_y = plan->size.h / game->editor->map->mapSize.y;
	plan->case_size = (fit_x < fit_y) ? fit_x : fit_y;
	if (plan->case_size < 1.0f)
		plan->case_size = 1.0f;

	plan->scale_max = (plan->size.h < plan->size.w) ? plan->size.h : plan->size.w;
	plan->scale_min = plan->case_size;
	plan->center.x = game->editor->map->mapSize.x / 2;
	plan->center.y = game->editor->map->mapSize.y / 2;

	return ;
}

/* Met à jour la taille de la grille. */
void	update_grid_size(t_game *game)
{
	t_list			*current = game->editor->text_inputs;
	t_text_input	*input;
	int				vinput;

	while (current)
	{
		input = (t_text_input *)current->content;

		vinput = ft_atoi(input->text);
		if (!ft_strcmp("mapX", input->name) && vinput > 0 && vinput <= 1000)
			game->editor->map->mapSize.x = vinput;
		vinput = ft_atoi(input->text);
		if (!ft_strcmp("mapY", input->name) && vinput > 0 && vinput <= 1000)
			game->editor->map->mapSize.y = vinput;

		current = current->next;
	}

	fit_grid_view(game);

	return ;
}
