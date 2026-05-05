/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_text_inputs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:38:08 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 12:30:57 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

static void	draw_case(t_game *game, t_text_input *input)
{
	SDL_Rect	box = input->box;

	to_responsive(game->window, &box);
	SDL_SetRenderDrawColor(game->window->renderPTR, 255, 255, 255, 255);
	SDL_RenderFillRect(game->window->renderPTR, &box);
	SDL_SetRenderDrawColor(game->window->renderPTR, 0, 0, 0, 255);
	SDL_RenderDrawRect(game->window->renderPTR, &box);

	return ;
}

static void	draw_text(t_game *game, t_text_input *input, char *text)
{
	SDL_Color black = {0, 0, 0, 255};
	SDL_Surface *surf = TTF_RenderUTF8_Blended(game->editor->font, text, black);
	if (surf)
	{
		SDL_Texture *tex = SDL_CreateTextureFromSurface(game->window->renderPTR, surf);
		SDL_Rect dst;
		int padding = 5;
		int max_w = input->box.w - 2 * padding;
		if (surf->w > max_w)
			dst.x = input->box.x + padding - (surf->w - max_w);
		else
			dst.x = input->box.x + padding;
		dst.y = input->box.y + (input->box.h - surf->h) / 2;
		dst.w = surf->w;
		dst.h = surf->h;

		SDL_RenderSetClipRect(game->window->renderPTR, &input->box);
		SDL_RenderCopy(game->window->renderPTR, tex, NULL, &dst);
		SDL_RenderSetClipRect(game->window->renderPTR, NULL);

		SDL_DestroyTexture(tex);
		SDL_FreeSurface(surf);
	}

	return ;
}

/* Draw the text of all inputs in them */
void	display_text_input(t_game *game, t_list **lst)
{
	t_list			*current = *lst;
	t_text_input	*input  = NULL;
	char			temp[201];

	while (current)
	{
		input = (t_text_input *)current->content;

		draw_case(game, input);
		if (input == game->editor->selected)
		{
			temp[0] = 0;
			ft_strlcat(temp, input->text, sizeof(temp));
			ft_strlcat(temp, "|", sizeof(temp));
			draw_text(game, input, temp);
		}
		else
			draw_text(game, input, input->text);

		current = current->next;
	}

	return ;
}
