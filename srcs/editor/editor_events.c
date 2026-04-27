/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:50:59 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/27 19:05:48 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

static void handle_input(t_editor *editor, char *text)
{
	if (!editor->selected)
		return ;
	if (ft_strlen(editor->selected->text) + ft_strlen(text) < sizeof(editor->selected->text))
		ft_strlcat(editor->selected->text, text, sizeof(editor->selected->text));

	return ;
}

static void handle_key(t_editor *editor, SDL_Keycode code, t_game *game)
{
	if (!editor->selected)
		return ;
	if (code == SDLK_BACKSPACE && ft_strlen(editor->selected->text))
		editor->selected->text[ft_strlen(editor->selected->text) - 1] = 0;
	else if (code == SDLK_ESCAPE)
		exit_game(game, NULL);
}

void	editor_events(t_game *game)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
				exit_game(game, NULL);
				break ;

			case SDL_TEXTINPUT:
				handle_input(game->editor, e.text.text);
				break ;

			case SDL_KEYDOWN:
				handle_key(game->editor, e.key.keysym.sym, game);
				break ;

			default:
				break;
		}
	}

	return ;
}
