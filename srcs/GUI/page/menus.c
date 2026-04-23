/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 23:32:07 by lucas             #+#    #+#             */
/*   Updated: 2026/04/21 15:34:34 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

void draw_current_menu(t_game *game)
{
    switch (game->window->menus.current)
    {
    case 0:
        send_rays(game);
		SDL_UpdateTexture(game->frame, NULL, game->frame_buffer, game->screenSize[0] * sizeof(Uint32));
		SDL_RenderCopy(game->window->renderPTR, game->frame, NULL, NULL);
        break;
    case 1:
        draw_main_menu(game);
        break;
    case 2:
        draw_settings_menu(game);
        break;
    default:
        break;
    }
}