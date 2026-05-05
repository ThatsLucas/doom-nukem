/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_selector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:14:22 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 19:18:02 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

void draw_texture_rounded(int x, int y, int w, int h, t_WIN *win, SDL_Texture *texture)
{
	SDL_Rect dest = {x, y, w, h};
	to_responsive(win, &dest);
	SDL_RenderCopy(win->renderPTR, texture, NULL, &dest);
	SDL_RenderDrawRect(win->renderPTR, &dest);

	return ;
}

static void draw_background(t_game *game)
{
	SDL_Rect	rectangle;

	rectangle.x = 680;
	rectangle.y = 525;
	rectangle.w = 750;
	rectangle.h = 400;

	to_responsive(game->window, &rectangle);
	SDL_SetRenderDrawColor(game->window->renderPTR, 255, 255, 255, 255);
	SDL_RenderFillRect(game->window->renderPTR, &rectangle);

	SDL_SetRenderDrawColor(game->window->renderPTR, 0, 0, 0, 255);
	SDL_RenderDrawRect(game->window->renderPTR, &rectangle);
}

static void draw_texture_grid(t_game *game)
{
	int			pos_x, pos_y;

	for (int i = 0; i < 3; i++)
	{
		pos_y = 555 + i * 120;
		for (int y = 0; y < 5; y++)
		{
			pos_x = 710 + y * 120;

			if (i * 5 + y + game->editor->texture_selector.page * 15 < game->editor->textures->num_textures)
				draw_texture_rounded(pos_x, pos_y, 100, 100,
					game->window, game->editor->textures->textures[i * 5 + y + game->editor->texture_selector.page * 15]);
		}
	}

	draw_texture(1320, 618, 100, 100, game->window, game->editor->texture_selector.buttons[0]);
	draw_texture(1320, 733, 100, 100, game->window, game->editor->texture_selector.buttons[1]);
	draw_texture(1370, 535, 50, 50, game->window, game->editor->texture_selector.buttons[2]);

	return ;
}

void	draw_texture_selector(t_game *game)
{
	if (!game->editor->texture_selector.display)
		return ;

	draw_background(game);
	draw_texture_grid(game);

	return ;
}
