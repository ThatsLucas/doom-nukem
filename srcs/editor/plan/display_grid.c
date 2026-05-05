/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:23:50 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 11:53:01 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Display the plan grid (with zoom) */
void	display_grid(t_game *game)
{
	t_editor	*editor = game->editor;
	int			start_x, start_y, end_x, end_y;
	int			offset_x, offset_y;

	offset_x = (editor->plan.size.w / 2.0f) - editor->plan.center.x * editor->plan.case_size;
	offset_y = (editor->plan.size.h / 2.0f) - editor->plan.center.y * editor->plan.case_size;

	start_x = offset_x;
	start_y = offset_y;

	end_x	= start_x + editor->plan.case_size * game->mapSize[0];
	end_y	= start_y + editor->plan.case_size * game->mapSize[1];

	SDL_Rect	r = (SDL_Rect){ .x = start_x, .y = start_y, .w = end_x - start_x, .h = end_y - start_y};
	SDL_SetRenderDrawColor(game->window->renderPTR, 190, 190, 190, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(game->window->renderPTR, &r);
	SDL_SetRenderDrawColor(game->window->renderPTR, 189, 17, 17, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(game->window->renderPTR, &r);
	for (int i = 0; i <= game->mapSize[0]; ++i)
		SDL_RenderDrawLine(game->window->renderPTR, i * editor->plan.case_size + start_x, start_y, i * editor->plan.case_size + start_x, end_y);

	for (int i = 0; i <= game->mapSize[1]; ++i)
		SDL_RenderDrawLine(game->window->renderPTR, start_x, i * editor->plan.case_size + start_y, end_x, i * editor->plan.case_size + start_y);

	return ;
}
