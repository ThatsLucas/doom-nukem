/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 23:32:07 by lucas             #+#    #+#             */
/*   Updated: 2026/05/18 17:12:51 by lle-duc          ###   ########.fr       */
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
        display_hud(game);
        break;
    case 1:
        draw_main_menu(game);
        break;
    case 2:
        draw_settings_menu(game);
        break;
    case 3:
        draw_lobby_menu(game);
        break;
    case 4:
        draw_lobby_multiplayer_menu(game);
        break;
    default:
        break;
    }
}