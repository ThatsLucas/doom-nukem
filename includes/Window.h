/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:41:07 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/04 17:18:37 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

#include "../deps/sdl2/include/SDL2/SDL.h"

typedef struct s_WIN
{
    SDL_Window* winPTR;
    SDL_Renderer* renderPTR;
}	t_WIN;

t_WIN* create_window(const char *title, int x, int y, int w, int h, Uint32 flags);

#endif