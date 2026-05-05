/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:21:13 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 20:08:44 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EDITOR_H
# define EDITOR_H

# include <SDL.h>
# include <SDL_ttf.h>
# include "Raycasting/Types.h"

typedef struct s_game		t_game;
typedef struct s_list		t_list;
typedef struct s_buttons	t_buttons;
typedef struct s_png		t_png;

typedef struct s_size2
{
	int	w;
	int	h;
}		t_size2;

typedef struct	s_text_input
{
	char		text[200];
	char		*name;
	SDL_Rect	box;
	SDL_Rect	dst;
}				t_text_input;

typedef struct	s_plan
{
	t_vect2	center;
	float	scale_min;
	float	scale_max;
	float	case_size;
	t_size2	size;
}			t_plan;

typedef struct	s_editor_textures
{
	SDL_Texture	**textures;
	t_png		*png;
	int			num_textures;
	int			cap_textures;
}				t_editor_textures;

typedef struct s_texture_selector
{
	int			display;
	int			page;
	int			num_page;
	void		**variable_to_set;
	SDL_Texture	*buttons[3];
}				t_texture_selector;


typedef struct	s_editor
{
	TTF_Font			*font;
	t_list				*text_inputs;
	t_text_input		*selected;
	t_buttons			*buttons;
	t_size2				settings;
	t_plan				plan;
	t_editor_textures	*textures;
	t_texture_selector	texture_selector;
}						t_editor;

/* Init / Exit */
void	init_editor(t_game *game);
void	init_editor_cache(t_game *game);
void	exit_editor(t_game *game);

/* Text Inputs */
void	add_text_inputs(t_game *game, SDL_Rect coords, char *name);
void	display_text_input(t_game *game, t_list **lst);
void	get_selected_input(t_game *game, t_list **lst, int x, int y);

/* Display */
void	display_editor(t_game *game);
void	display_grid(t_game *game);
void	init_settings_global_buttons(t_game *game);
void	init_settings_global_inputs(t_game *game);
void	display_separators(t_game *game);

/* Texture Selector */
void	draw_texture_selector(t_game *game);
int		get_clicked_editor_button(t_game *game, int x, int y);
void	create_texture_selector(t_game *game, void **addr);
void	get_clicked_texture(t_game *game, int x, int y);

/* Events */
void	editor_events(t_game *game);
void	plan_click(t_game *game, SDL_MouseMotionEvent *motion);
void	handle_zoom(t_editor *editor, SDL_MouseWheelEvent *wheel);

/* Utils */
void	update_grid_size(t_game *game);
t_vect2	pixels_to_pos(t_editor *editor, float x, float y);
t_vect2	pos_to_pixels(t_editor *editor, float x, float y);

#endif