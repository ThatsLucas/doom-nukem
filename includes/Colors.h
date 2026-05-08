/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:19:11 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/07 17:04:58 by edurance         ###   ########.fr       */
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