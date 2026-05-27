/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udp_communication.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:46:06 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/27 16:20:32 by lle-duc          ###   ########.fr       */
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

    send_UDP_request(datas, connection);

    return (1);
}

int send_player_pos(t_udp_connections *connection, t_client_udp_datas *datas)
{
    send_UDP_request(datas, connection);
    return (1);
}

void handle_server_response(t_game *game, t_udp_connections *connection)
{
    t_server_udp_datas serverDatas;
    ft_bzero(&serverDatas, sizeof(t_server_udp_datas));
    if (get_server_response(connection, &serverDatas))
    {
        ft_printf("Received msg from server\n");
        handle_server_notifications_request(&serverDatas, game);
        ft_printf("Server response = %d\n", serverDatas.state);
    }
}