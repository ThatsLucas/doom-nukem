/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:16:04 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/27 16:08:40 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_SERVER_H
#define MULTI_SERVER_H

#include "../../libft/include/libft.h"
#include "multiplayer/shared.h"

#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <SDL.h>

void *create_server(void *gameStruct);

typedef struct s_game t_game;

typedef struct s_udp_server_status
{
    int currentState;
    int serverSocket;
    int playerCount;
    struct sockaddr address[4];
    Uint64 last_update[4];
    double players[4][2];
} t_udp_server_status;

void send_to_client(t_server_udp_datas *datas, struct sockaddr *addr, int socket);
void send_notifications(t_game *game, struct sockaddr *addr, char *str, int duration, int fontsize);
void broadcast_notifications(t_game *game, int except, char *str, int duration, int fontsize);
int is_player_connected(t_game *game, struct sockaddr *client);
int add_new_player(t_game *game, struct sockaddr *newClient);

#endif
