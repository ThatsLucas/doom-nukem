/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cinematic_bars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:32:44 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/20 10:42:27 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"
#include "Window.h"

void draw_cinematic_bars(t_RGB rgb, t_WIN *win)
{
    SDL_Rect RectPos = {0, 0, 1920, 200};
    to_responsive(win, &RectPos);
    create_rectangle(win->renderPTR, RectPos, rgb);

    RectPos = (SDL_Rect){0, 880, 1920, 200};
    to_responsive(win, &RectPos);
    create_rectangle(win->renderPTR, RectPos, rgb);
}