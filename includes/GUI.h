/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GUI.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:12:34 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/10 21:03:28 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

#include <SDL.h>
#include "Colors.h"
#include "parser/PNG.h"

typedef struct s_ply t_ply;
typedef struct s_WIN t_WIN;

typedef struct s_coordinates
{
    int x;
    int y;
    int w;
    int h;
}				t_coordinates;

typedef struct s_buttons
{
    t_coordinates buttonCoords;
    t_RGB color;
    t_RGB hoverColor;
    void (*callback_func)(t_WIN *);
    struct s_buttons *next;
}   t_buttons;

/*utils*/
void	get_screen_size(int *w, int *h);
void	draw_player(SDL_Renderer *renderer, t_ply *ply, int size, t_RGB color);

/*circles*/
int		SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius, t_RGB rgb);
int		SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius, t_RGB rgb);

/*rectangles*/
void    create_rectangle(SDL_Renderer *renderer, t_coordinates coords, t_RGB rgb);

/*buttons*/
void    create_button(t_buttons **button_list, void (*callback)(t_WIN *), t_coordinates coords, t_RGB color, t_RGB hoverColor);
int     check_button_pressed(t_WIN *win, t_buttons *button_list);
void    display_buttons(t_buttons *button_list, SDL_Renderer *renderer);
void    free_buttons(t_buttons *buttonlist);

/*Images*/
SDL_Texture *create_image(t_png *pngFile, SDL_Renderer *renderer);


#endif