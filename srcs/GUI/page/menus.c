/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 23:32:07 by lucas             #+#    #+#             */
/*   Updated: 2026/05/21 11:59:04 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"
#include "multiplayer/shared.h"

void draw_current_menu(t_game *game)
{
    switch (game->window->menus.current)
    {
    case 0:
        t_udp_datas datas; // TODO: just for testing remove this shit and make it good
        datas.state = 1;
        datas.x = game->ply->pos.x;
        datas.y = game->ply->pos.y;
        printf("player pos x = %f y = %f\n", datas.x, datas.y);
        send_join_request("127.0.0.1", &datas);
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
    case 5:
        draw_cinematic_one(game);
        break;
    case 6:
        draw_cinematic_two(game);
        break;
    default:
        break;
    }
}