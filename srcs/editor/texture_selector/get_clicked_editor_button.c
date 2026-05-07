/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clicked_editor_button.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:39:31 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/07 11:31:36 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

int	check_close_button(t_game *game, int x, int y)
{
	SDL_Rect	close = {.x = 1370, .y = 535, .w = 50, .h = 50};

	to_responsive(game->window, &close);
	if (x <= close.x + close.w && x > close.x && y <= close.y + close.h && y > close.y)
	{
		game->editor->texture_selector.display = 0;
		return (1);
	}
	return (0);
}

int	get_clicked_editor_button(t_game *game, int x, int y)
{
	SDL_Rect	up = {.x = 1320, .y = 618, .w = 100, .h = 100};
	SDL_Rect	down = {.x = 1320, .y = 733, .w = 100, .h = 100};

	if (!game->editor->texture_selector.display)
		return (0);

	to_responsive(game->window, &up);
	to_responsive(game->window, &down);

	if (x <= up.x + up.w && x > up.x && y <= up.y + up.h && y > up.y)
	{
		if (game->editor->texture_selector.page > 0)
			(game->editor->texture_selector.page)--;
		return (1);
	}
	if (x <= down.x + down.w && x > down.x && y <= down.y + down.h && y > down.y)
	{
		if (game->editor->texture_selector.page < game->editor->texture_selector.num_page - 1)
			(game->editor->texture_selector.page)++;
		return (1);
	}

	if (check_close_button(game, x, y))
		return (1);
	return (0);
}
