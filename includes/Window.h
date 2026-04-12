/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:41:07 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/11 23:48:19 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

#include <SDL.h>
#include "GUI.h"

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