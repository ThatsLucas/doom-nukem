/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:19:11 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/04 17:18:29 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

#include "../deps/sdl2/include/SDL2/SDL.h"

typedef struct s_RGB
{
    Uint8  r;
    Uint8  g;
    Uint8  b;
    Uint8  alphaValue;
}	t_RGB;

#endif