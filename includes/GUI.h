/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GUI.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:12:34 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/16 23:34:04 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../libft/include/libft.h"
#include "Colors.h"
#include "Raycasting/Types.h"

typedef struct s_ply	t_ply;
typedef struct s_WIN	t_WIN;
typedef struct s_game	t_game;
typedef struct s_vect2	t_vect2;
typedef struct s_png	t_png;

typedef struct s_font
{
    TTF_Font    *font;
    char        *str;
    int         size;
    SDL_Color   color;
    SDL_Texture *texture;
    int w;
    int h;
    int     textHOffset; // ya des  fonts de merde qui renvoie pas la bonne hauteur du texte
}   t_font;

typedef struct s_buttons
{
    SDL_Rect buttonCoords;
    t_RGB color;
    t_RGB hoverColor;
    void (*callback_func)(t_game *);
    struct s_buttons *next;
    t_font *text;
    t_font *textHover;
    int page_id; // 1 = main menu, 2 = ?
}   t_buttons;

/*utils*/
void	get_screen_size(int *w, int *h);
void	display_fps(t_game *game);

/*circles*/
int		SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius, t_RGB rgb);
int		SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius, t_RGB rgb);

/*rectangles*/
void    create_rectangle(SDL_Renderer *renderer, SDL_Rect coords, t_RGB rgb);

/*buttons*/
void    create_button(t_buttons **button_list, void (*callback)(t_game *), SDL_Rect coords, t_RGB color, t_RGB hoverColor, t_font *text, t_font *textHover, int pageID);
int     check_button_pressed(t_game *win, t_buttons *button_list);
void	display_buttons(t_buttons *button_list, t_game *game, int pageID);
void    free_buttons(t_buttons *buttonlist);

/*minimap*/
void	draw_player(SDL_Renderer *renderer, t_game *game, int size, t_RGB color);

/* gameplay */
Uint32	write_color(int r, int g, int b, int sect_light);
void	draw_ceil(t_game *game, t_ray *ray, int x, t_sector *sector);
void	draw_wall(t_game *game, t_ray *ray, int x, t_sector *sector);
void	draw_floor(t_game *game, t_ray *ray, int x, t_sector *sector);
void	draw_offsets(t_ray *ray, t_game *game, int ny_top, int ny_bot, int x, t_sector *sector);

/*Images*/
SDL_Texture *create_image(t_png *pngFile, SDL_Renderer *renderer);

/*Text*/
void create_text(t_font *textData, SDL_Renderer  *renderer, char *text, char *fontPath);
void create_text_multiple_lines(t_font *textData, SDL_Renderer  *renderer, char *text, char *fontPath, uint32_t maxW);

/*RESPONSIVENESS*/
void to_responsive(t_WIN *win, SDL_Rect *cur);

#endif