/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:21:13 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/08 15:04:12 by aabouyaz         ###   ########.fr       */
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
typedef struct s_font		t_font;
typedef struct s_WIN		t_WIN;

# ifndef EPSILON
#  define EPSILON 0.1
# endif

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
	int			page;
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
	SDL_Texture	**variable_to_set;
	SDL_Texture	*buttons[3];
}				t_texture_selector;

typedef struct s_text_select_button
{
	int			page;
	SDL_Texture	**texture;
	SDL_Rect	box;
}		t_text_select_button;

typedef struct	s_editor_properties
{
	int			selected_property;		// 0: cursor vide / 1: walls / 2: slope / 3: sectors
	TTF_Font	*font;
	SDL_Texture	*walls[3];
	SDL_Texture	*sectors[3];
	int			draw_wall_active;
	int			last_vertex;
}		t_editor_properties;

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
	t_font				*error_text;
	SDL_Texture			*buttons_textures[6];
	int					selected_tool;
	t_map				*map;
	t_editor_properties	properties;
	t_list				*texture_selector_buttons;
}						t_editor;

/* Init / Exit */
void	init_editor(t_game *game);
void	init_editor_cache(t_game *game);
void	exit_editor(t_game *game);

/* Text Inputs */
void	add_text_inputs(t_game *game, SDL_Rect coords, char *name, int page);
void	display_text_input(t_game *game, t_list **lst);
void	get_selected_input(t_game *game, t_list **lst, int x, int y);

/* Display */
void	init_settings_global_buttons(t_game *game);
void	init_settings_global_inputs(t_game *game);
void	init_action_buttons(t_game *game);
void	display_editor(t_game *game);
void	display_grid(t_game *game);
void	display_separators(t_game *game);
void	display_editor_map(t_game *game);

/* Texture Selector */
void	draw_texture_selector(t_game *game);
int		get_clicked_editor_button(t_game *game, int x, int y);
void	create_texture_selector(t_game *game, SDL_Texture **addr);
void	get_clicked_texture(t_game *game, int x, int y);
void	draw_texture_rounded(int x, int y, int w, int h, t_WIN *win, SDL_Texture *texture);
void	add_texture_selector_button(t_game *game, SDL_Texture **text, int page, SDL_Rect box);
void	display_texture_selector_button(t_game *game);
void	get_clicked_texture_button(t_game *game, int x, int y);

/* Events */
void	editor_events(t_game *game);
void	plan_click(t_game *game, SDL_Event *e);
void	handle_zoom(t_editor *editor, SDL_MouseWheelEvent *wheel);

/* Utils */
void	update_grid_size(t_game *game);
t_vect2	pixels_to_pos(t_editor *editor, float x, float y);
t_vect2	pos_to_pixels(t_editor *editor, float x, float y);
void	precompute_mirrors(t_map *map);
int		point_on_segment(t_vect2 a, t_vect2 b, t_vect2 c, float eps);
int		find_sector(t_map *map, t_vect2 p);
int		get_wall_index(t_map *map, float x, float y);

/* Properties */
void	draw_prop_text(t_game *game, char *txt, int x, int y);
void	init_properties(t_game *game);
void	display_properties(t_game *game);
void	init_walls_properties(t_game *game);
void	display_walls_property(t_game *game);
void	editor_place_wall(t_game *game, int pixx, int pixy, int button);
void	display_sector_property(t_game *game);
void	init_sector_properties(t_game *game);

/* Map Editor */
void	init_editor_map(t_game *game);
void	map_realloc(t_game *game, void **pointer, int *cap, unsigned int sizeofone);
int		editor_add_vertice(t_game *game, float x, float y);
void	editor_add_wall(t_game *game, int v1, int v2);
t_vect2	*get_clicked_vertice(t_game *game, float x, float y);
void	clear_editor_plan(t_game *game);
void	compute_sectors(t_map *map);
void	suppress_vertice(t_game *game, float x, float y);
void	suppress_wall(t_game *game, int wall_indx);

#endif
