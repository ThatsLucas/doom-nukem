/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:41:07 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/02 11:29:28 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

#include <SDL.h>
#include "GUI/GUI.h"
#include "menus/menus.h"

#define DNFONT "assets/fonts/AmazDooMLeft.ttf"
#define DNFONTOUTLINED "assets/fonts/AmazDooMLeftOutline.ttf"


typedef struct s_WIN
{
    SDL_Window*     winPTR;
    SDL_Renderer*   renderPTR;
    t_buttons*      buttonList;
    int             w;
    int             h;
    t_menus         menus;
    
}	t_WIN;

t_WIN* create_window(const char *title, int x, int y, int w, int h, Uint32 flags);

#endif