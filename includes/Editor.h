/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:21:13 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/30 12:37:35 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EDITOR_H
# define EDITOR_H

# include <SDL.h>
# include <SDL_ttf.h>

typedef struct s_game		t_game;
typedef struct s_list		t_list;
typedef struct s_buttons	t_buttons;

typedef struct s_text_input
{
	char		text[200];
	char		*name;
	SDL_Rect	box;
	SDL_Rect	dst;
}				t_text_input;

typedef struct s_editor
{
	TTF_Font		*font;
	t_list			*text_inputs;
	t_text_input	*selected;
	t_buttons		*buttons;
}				t_editor;

/* Init / Exit */
void	init_editor(t_game *game);
void	exit_editor(t_game *game);

/* Text Inputs */
void	add_text_inputs(t_game *game, SDL_Rect coords, char *name);
void	display_text_input(t_game *game, t_list **lst);
void	get_selected_input(t_editor *editor, t_list **lst, int x, int y);

/* Display */
void	display_editor(t_game *game);
void	display_grid(t_game *game);

/* Event Handler */
void	editor_events(t_game *game);

#endif