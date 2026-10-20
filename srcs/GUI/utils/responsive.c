/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responsive.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:06:25 by lucas             #+#    #+#             */
/*   Updated: 2026/04/13 10:40:30 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"
#include "Window.h"

/* Adapte un rectangle à la taille de la fenêtre. */
void to_responsive(t_WIN *win, SDL_Rect *cur)
{
    cur->w = (cur->w * win->w) / 1920;
    cur->h = (cur->h * win->h) / 1080;
    cur->x = (cur->x * win->w) / 1920;
    cur->y = (cur->y * win->h) / 1080;
}