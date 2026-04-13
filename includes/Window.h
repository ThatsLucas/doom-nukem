/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:41:07 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/13 10:37:52 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

#include <SDL.h>
#include "GUI/GUI.h"

typedef struct s_WIN
{
    SDL_Window* winPTR;
    SDL_Renderer* renderPTR;
    t_buttons* buttonList;
    int w;
    int h;
}	t_WIN;

t_WIN* create_window(const char *title, int x, int y, int w, int h, Uint32 flags);

#endif