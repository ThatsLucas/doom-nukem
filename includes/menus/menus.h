/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root- <root-@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:33:17 by lucas             #+#    #+#             */
/*   Updated: 2026/04/13 14:06:26 by root-            ###   ########.fr       */
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

/*MAIN MENU*/

void draw_main_menu(t_main_menu *MainMenu, t_game *game);
int init_home_menu(t_WIN *win, SDL_Renderer *renderer, t_main_menu *MainMenu, int button_offset);
void destroy_main_menu(t_main_menu *MainMenu);

#endif