/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GUI.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:12:34 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/04 18:35:22 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

#include "../deps/sdl2/include/SDL2/SDL.h"
#include "Colors.h"

void create_rectangle(SDL_Renderer *renderer, int x, int y, int w, int h, t_RGB rgb);
void get_screen_size(int *w, int *h);

#endif