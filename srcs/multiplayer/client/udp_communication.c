/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udp_communication.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:46:06 by lle-duc           #+#    #+#             */
/*   Updated: 2026/09/23 11:41:19 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/client.h"
#include "Game.h"

void send_UDP_request(t_client_udp_datas *datas, t_udp_connections *connection)
{
    sendto(connection->con_socket, datas, sizeof(t_client_udp_datas), MSG_CONFIRM, (struct sockaddr *)&connection->servaddr, sizeof(connection->servaddr));
}

int connect_player(t_udp_connections *connection, char *serveraddr, t_client_udp_datas *datas)
{
    ft_bzero(connection, sizeof(*connection));
    connection->servaddr.sin_addr.s_addr = inet_addr(serveraddr);
    connection->servaddr.sin_port = htons(PORT);
    connection->servaddr.sin_family = AF_INET;

    connection->con_socket = socket(AF_INET, SOCK_DGRAM, 0);
    fcntl(connection->con_socket, F_SETFL, O_NONBLOCK);

    datas->state = 1;

    if (connect(connection->con_socket, (struct sockaddr *)&connection->servaddr, sizeof(connection->servaddr)) < 0)
    {
        ft_printf("\n Error: could not connect to the host! \n");
        return (0);
    }
    connection->is_connected = 1;

    send_UDP_request(datas, connection);

    return (1);
}

void close_connection(t_game *game)
{
    close(game->clientConnection.con_socket);
    ft_bzero(&game->clientConnection, sizeof(t_udp_connections));
    game->settings.multiplayer_enabled = 0;
    game->settings.is_host = 0;
}
// TODO disconnect_player

static int get_latest_server_response(t_udp_connections *connection, t_server_udp_datas *datas)
{
    t_server_udp_datas latest;
    t_server_udp_datas last_notif;
    int has_data = 0;
    int has_notif = 0;

    while (get_server_response(connection, &latest))
    {
        *datas = latest;
        has_data = 1;
        if (latest.is_notif)
        {
            last_notif = latest;
            has_notif = 1;
        }
    }
    if (has_notif)
    {
        datas->is_notif = last_notif.is_notif;
        datas->notif_duration = last_notif.notif_duration;
        datas->notif_font_size = last_notif.notif_font_size;
        ft_strlcpy(datas->notif_str, last_notif.notif_str, sizeof(datas->notif_str));
    }
    return (has_data);
}

void handle_server_response(t_game *game, t_udp_connections *connection)
{
    t_server_udp_datas serverDatas;

    if (!game->clientConnection.is_connected)
        return;
    ft_bzero(&serverDatas, sizeof(t_server_udp_datas));
    if (get_latest_server_response(connection, &serverDatas))
    {
        handle_server_notifications_request(&serverDatas, game);
        handle_game_state(&serverDatas, game);
        game->clientConnection.last_update = SDL_GetTicks64();
        game->clientConnection.selfIndex = serverDatas.playerIndex;
    }
    else
    {
        Uint64 curTime = SDL_GetTicks64();
        if (game->clientConnection.last_update + TIMEOUT_DURATION < curTime) // server do not responded in time
        {
            close_connection(game);
            create_notif(&game->window->menus.notif.notif_buf, "Connection to host lost!", 5, 70);
            game->window->menus.current = 4;
        }
    }
}