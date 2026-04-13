/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:33:17 by lucas             #+#    #+#             */
/*   Updated: 2026/04/14 00:01:33 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENUS_H
#define MENUS_H

#include "Window.h"
#include <SDL.h>

typedef struct s_main_menu {
    t_png background;
    t_png logo;
    t_png button;
    t_font btn_one_text;
    t_font btn_one_text_hover;
    t_font btn_two_text;
    t_font btn_two_text_hover;
    t_font btn_three_text;
    t_font btn_three_text_hover;
    int has_init;
} t_main_menu;

#define NOTIF_NOT_SHOWED    0
#define NOTIF_SPAWNING      1
#define NOTIF_DELETING      2

typedef struct s_notif {
    char *text;
    int duration; // in ms
    int time_left; // in ms
    int state; // 0 not showed yet, 1 moving to pos, 2 going back to no show
    SDL_Rect coords;
}               t_notif;

typedef struct s_notif_buf {
    t_notif         *notif;
    struct s_notif_buf     *next;
}               t_notif_buf;

/*MAIN MENU*/

void draw_main_menu(t_main_menu *MainMenu, t_game *game);
int init_home_menu(t_WIN *win, SDL_Renderer *renderer, t_main_menu *MainMenu, int button_offset);
void destroy_main_menu(t_main_menu *MainMenu);

/*NOTIFS*/
int init_notif(t_png *notifImg, SDL_Renderer *renderer);
void create_notif(t_notif_buf **notif_buf, char *str, int duration_ms);
void display_notif(t_WIN *win, t_notif_buf **notif_buf);

#endif