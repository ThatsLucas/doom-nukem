/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_click.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:37:26 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/08 11:14:12 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Check if the texture_selector is displayed and the cursor was on it */
static int	check_selector_clicked(t_game *game, int x, int y)
{
	SDL_Rect	box = {.x = 680, .y = 525, .w = 750, .h = 400};

	if (!game->editor->texture_selector.display)
		return (0);

	to_responsive(game->window, &box);

	if (x <= box.x + box.w && x > box.x && y <= box.y + box.h && y > box.y)
		return (1);
	return (0);
}

/* Manage when plan is clicked */
void	plan_click(t_game *game, SDL_MouseMotionEvent *motion)
{
	static int	plan_clicked = 0;
	static int	last_x = 0, last_y = 0;

	if (motion->x > game->editor->plan.size.w)
		return ;

	if (check_selector_clicked(game, motion->x, motion->y))
		return ;

	if (motion->type == SDL_MOUSEBUTTONDOWN && game->editor->selected_tool > 0)
	{
		editor_place_wall(game, motion->x, motion->y);
		return ;
	}

	if (plan_clicked && motion->type == SDL_MOUSEBUTTONUP)
	{
		last_x = 0;
		last_y = 0;
		plan_clicked = 0;
	}
	else if (!plan_clicked && motion->type == SDL_MOUSEBUTTONDOWN)
		plan_clicked = 1;

	if (plan_clicked)
	{
		if (last_x)
			game->editor->plan.center.x += (last_x - motion->x) / (float)game->editor->plan.case_size;
		last_x = motion->x;
	}

	if (plan_clicked)
	{
		if (last_y)
			game->editor->plan.center.y += (last_y - motion->y) / (float)game->editor->plan.case_size;
		last_y = motion->y;
	}

	return ;
}
