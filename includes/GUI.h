/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GUI.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:12:34 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/11 13:00:41 by aabouyaz         ###   ########.fr       */
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
void	draw_wall(t_game *game, t_vect2 a, t_vect2 b, t_RGB color);
void	draw_walls(t_game *game, t_RGB rgb);
void	draw_player(SDL_Renderer *renderer, t_game *game, int size, t_RGB color);

/*Gameplay*/
void	send_rays(t_game *game, t_RGB rgb);
void	texture_wall(t_game *game, t_ray *ray);
void	texture_floor(t_game *game, t_ray *rays);
void	texture_ceiling(t_game *game, t_ray *rays);

#endif