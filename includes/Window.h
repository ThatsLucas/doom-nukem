/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root- <root-@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:41:07 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/13 13:59:06 by root-            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

#include <SDL.h>
#include "GUI.h"
#include "menus/menus.h"

typedef struct s_WIN
{
    SDL_Window* winPTR;
    SDL_Renderer* renderPTR;
    t_buttons* buttonList;
    int w;
    int h;
    t_main_menu MainMenu;
}	t_WIN;

t_WIN* create_window(const char *title, int x, int y, int w, int h, Uint32 flags);

#endif