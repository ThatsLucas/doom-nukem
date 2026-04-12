/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_notif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:46:10 by lucas             #+#    #+#             */
/*   Updated: 2026/04/12 21:58:58 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"

// static void init_notif(t_png *notifImg)
// {
//     if(!process_png(notifImg, "assets/png/notif/notif_bg.png"))
// 		return (0);
//     return (1);
// }

// void create_notif()
// {
//     static int hasInit = 0;
//     t_png notifImg;
//     if (!hasInit)
//         hasInit = init_notif(&notifImg);
//     MainMenu->background.texture = create_image(&MainMenu->background, renderer);

//     SDL_Surface * TTF_RenderText_Blended_Wrapped(TTF_Font *font, const char *text, SDL_Color fg, Uint32 wrapLength);
// }