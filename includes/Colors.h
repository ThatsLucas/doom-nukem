/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:19:11 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/04 19:57:59 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

#include <SDL.h>

typedef struct s_RGB
{
    Uint8  r;
    Uint8  g;
    Uint8  b;
    Uint8  alphaValue;
}	t_RGB;

#endif