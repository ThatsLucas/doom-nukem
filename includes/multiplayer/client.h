/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:15:18 by lle-duc           #+#    #+#             */
/*   Updated: 2026/07/06 13:23:32 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_CLIENT_H
#define MULTI_CLIENT_H

#include "../../libft/include/libft.h"
#include "multiplayer/shared.h"

#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <SDL.h>

typedef struct s_game t_game;

typedef struct s_udp_connections
{
    struct sockaddr_in servaddr;
    int con_socket;
    int is_connected;
    int selfIndex;
    int state;
    int player_count;
    Uint64 last_update;
    double players[4][2];
    double player_angles[4];
} t_udp_connections;

void send_UDP_request(t_client_udp_datas *datas, t_udp_connections *connection);
int get_server_response(t_udp_connections *connection, t_server_udp_datas *datas);
void handle_server_notifications_request(t_server_udp_datas *datas, t_game *game);
void handle_game_state(t_server_udp_datas *datas, t_game *game);
void render_multiplayer_players(t_game *game);

int connect_player(t_udp_connections *connection, char *serveraddr, t_client_udp_datas *datas);
void handle_server_response(t_game *game, t_udp_connections *connection);
void send_UDP_request(t_client_udp_datas *datas, t_udp_connections *connection);
void send_corresponding_datas_to_server(t_game *game);
void close_connection(t_game *game);

#endif
