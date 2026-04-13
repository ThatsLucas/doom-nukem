/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:33:17 by lucas             #+#    #+#             */
/*   Updated: 2026/04/12 18:18:00 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENUS_H
# define MENUS_H

#include <SDL.h>
#include "Window.h"

typedef struct s_main_menu
{
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
}				t_main_menu;

#endif