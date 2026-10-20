/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GUI.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:12:34 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/20 13:51:03 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "../libft/include/libft.h"
# include "Colors.h"
# include "GUI/HUD.h"
# include "Raycasting/Raycasting.h"
# include "parser/PNG.h"
# include <SDL.h>
# include <SDL_ttf.h>
# include <pthread.h>

typedef struct s_ply	t_ply;
typedef struct s_WIN	t_WIN;
typedef struct s_game	t_game;
typedef struct s_vect2	t_vect2;
typedef struct s_png	t_png;

typedef struct s_font
{
	TTF_Font			*font;
	char				*str;
	int					size;
	SDL_Color			color;
	SDL_Texture			*texture;
	int					w;
	int					h;
	int					textHOffset;	// ya des  fonts de merde qui renvoie pas la bonne hauteur du texte
}						t_font;

typedef struct s_buttons
{
	SDL_Rect			buttonCoords;
	t_RGB				color;
	t_RGB				hoverColor;
	void				(*callback_func)(t_game *);
	struct s_buttons	*next;
	t_font				*text;
	t_font				*textHover;
	int					page_id;
}						t_buttons;

/*utils*/
void					get_screen_size(int *w, int *h);
void					display_fps(t_game *game);
SDL_Color				RGBtoSDLColor(t_RGB color);
void					draw_line_thick(SDL_Renderer *ren, float x1, float y1, float x2, float y2, int thickness);
void					draw_cinematic_bars(t_RGB rgb, t_WIN *win);

/*circles*/
int						SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius, t_RGB rgb);
int						SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius, t_RGB rgb);

/*rectangles*/
void					create_rectangle(SDL_Renderer *renderer, SDL_Rect coords, t_RGB rgb);

/*buttons*/
int						is_mouse_pos_inside_button(SDL_Rect mouseCoords,SDL_Rect buttonCoords);
int						check_button_pressed(t_game *win, t_buttons *button_list);
void					display_buttons(t_buttons *button_list, t_game *game, int pageID);
void					free_buttons(t_buttons *buttonlist);
void					create_button(t_buttons **button_list, void (*callback)(t_game *), SDL_Rect coords,
							t_RGB color, t_RGB hoverColor, t_font *text, t_font *textHover, int pageID);

///* gameplay */
Uint32					write_color(int x, int y, t_game *game, t_RGB c, int sect_light);
void					draw_ceil(t_game *game, t_ray *ray, int x, t_sector *sector);
void					draw_wall(t_game *game, t_ray *ray, int x, t_sector *sector);
void					draw_floor(t_game *game, t_ray *ray, int x, t_sector *sector);
void					draw_offsets(t_ray *ray, t_game *game, int ny_top, int ny_bot, int x, t_sector *sector);

/*Images*/
SDL_Texture				*create_image(t_png *pngFile, SDL_Renderer *renderer);
SDL_Rect				get_png_opaque_bounds(t_png *pngFile);
t_tex					png_to_tex(t_png *png);
t_tex					*create_sprite(t_png *png);
void					draw_sprite_zbuf(t_game *game, t_tex *tex, SDL_Rect dest, float depth, int light);

/*Text*/
void					create_text(t_font *textData, SDL_Renderer *renderer, char *text, char *fontPath);
void					create_menu_button_texts(t_font *texts, SDL_Renderer *renderer, char *str);
void					create_white_text(t_font *font, SDL_Renderer *renderer, char *str, int size);
int						join_png_threads(pthread_t *threads, t_png **images, int count, SDL_Renderer *renderer);
void					create_text_multiple_lines(t_font *textData, SDL_Renderer *renderer, char *text, char *fontPath, uint32_t maxW);
void					destroy_text_texture(t_font *text);

/*RESPONSIVENESS*/
void					to_responsive(t_WIN *win, SDL_Rect *cur);

#endif
