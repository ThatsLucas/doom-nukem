/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:54:02 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/04 16:04:52 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

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
			game->mapSize[0] = vinput;
		vinput = ft_atoi(input->text);
		if (!ft_strcmp("mapY", input->name) && vinput > 0 && vinput <= 1000)
			game->mapSize[1] = vinput;

		current = current->next;
	}

	int offset_x = game->editor->plan.size.w / game->mapSize[0];
	int offset_y = game->editor->plan.size.h / game->mapSize[1];
	game->editor->plan.case_size = offset_x;
	if (offset_x > offset_y)
		game->editor->plan.case_size = offset_y;

	game->editor->plan.scale_max = (game->editor->plan.size.h < game->editor->plan.size.w) ? game->editor->plan.size.h : game->editor->plan.size.w;
	game->editor->plan.scale_min = game->editor->plan.case_size;
	game->editor->plan.center.x = (float)game->mapSize[0] / 2;
	game->editor->plan.center.y = (float)game->mapSize[1] / 2;

	return ;
}
