/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GUI.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:12:34 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/15 13:18:31 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

#include <SDL.h>
#include "Colors.h"
#include "Raycasting/Types.h"

typedef struct s_ply	t_ply;
typedef struct s_WIN	t_WIN;
typedef struct s_game	t_game;
typedef struct s_vect2	t_vect2;

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
    void (*callback_func)(t_game *);
    struct s_buttons *next;
}   t_buttons;

/*utils*/
void	get_screen_size(int *w, int *h);
void	display_fps(t_game *game);

/*circles*/
int		SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius, t_RGB rgb);
int		SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius, t_RGB rgb);

/*rectangles*/
void    create_rectangle(SDL_Renderer *renderer, t_coordinates coords, t_RGB rgb);

/*buttons*/
void    create_button(t_buttons **button_list, void (*callback)(t_game *), t_coordinates coords, t_RGB color, t_RGB hoverColor);
int     check_button_pressed(t_game *win, t_buttons *button_list);
void    display_buttons(t_buttons *button_list, SDL_Renderer *renderer);
void    free_buttons(t_buttons *buttonlist);

/*minimap*/
void	draw_player(SDL_Renderer *renderer, t_game *game, int size, t_RGB color);

/* gameplay */
Uint32	write_color(int r, int g, int b, int sect_light);
void	draw_ceil(t_game *game, t_ray *ray, int x, t_sector *sector);
void	draw_wall(t_game *game, t_ray *ray, int x, t_sector *sector);
void	draw_floor(t_game *game, t_ray *ray, int x, t_sector *sector);
void	draw_offsets(t_ray *ray, t_game *game, int ny_top, int ny_bot, int x, t_sector *sector);

#endif