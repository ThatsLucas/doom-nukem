/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:59:56 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/28 15:49:53 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/client.h"
#include "Game.h"

int get_server_response(t_udp_connections *connection, t_server_udp_datas *datas)
{
    ssize_t n = recvfrom(connection->con_socket, datas, sizeof(t_server_udp_datas), 0, NULL, NULL);
    if (n > 0 && n == sizeof(t_server_udp_datas))
    {
        // TODO checksum pour check si data corrompu ?
        return (1);
    }
    return (0);
}

void handle_server_notifications_request(t_server_udp_datas *datas, t_game *game)
{
    if (!datas->is_notif)
        return;
    create_notif(&game->window->menus.notif.notif_buf, datas->notif_str, datas->notif_duration, datas->notif_font_size);
}

void handle_game_state(t_server_udp_datas *datas, t_game *game)
{
    game->clientConnection.state = datas->state;
    game->clientConnection.player_count = datas->playerCount;
    ft_memcpy(game->clientConnection.players, datas->players, sizeof(datas->players));
    ft_memcpy(game->clientConnection.player_angles, datas->player_angles, sizeof(datas->player_angles));

    if (datas->state == 1)
        game->window->menus.current = 4;
    if (datas->state == 2)
    {
        int curMenu = game->window->menus.current;
        if ((curMenu > 5 && curMenu < 8) || curMenu == 0)
            return;

        switch (datas->level)
        {
        case 1:
            start_level_1(game);
            break;
        case 2:
            start_level_2(game);
            break;
        case 3:
            start_level_3(game);
            break;
        default:
            break;
        }
    }
    if (datas->state == 4)
    {
        close(game->clientConnection.con_socket);
        game->clientConnection.is_connected = 0;
        game->clientConnection.player_count = 0;
        game->clientConnection.state = 0;
        create_notif(&game->window->menus.notif.notif_buf, "The game is full!", 5, 70);
    }
}
