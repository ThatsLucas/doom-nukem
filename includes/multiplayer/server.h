/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:16:04 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/29 15:41:54 by lle-duc          ###   ########.fr       */
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
    int currentLevel;
    int serverSocket;
    int playerCount;
    struct sockaddr address[4];
    Uint64 last_update[4];
    double players[4][2];
    double player_angles[4];
} t_udp_server_status;

void send_to_client(t_server_udp_datas *datas, struct sockaddr *addr, int socket, int playerIndex);
void send_default_info_response(t_game *game);
void broadcast_message(t_game *game, int except, t_server_udp_datas *datas);
void send_notifications(t_game *game, struct sockaddr *addr, char *str, int duration, int fontsize, int playerIndex);
void broadcast_notifications(t_game *game, int except, char *str, int duration, int fontsize);
int is_player_connected(t_game *game, struct sockaddr *client);
int add_new_player(t_game *game, struct sockaddr *newClient);
void remove_player(t_game *game, struct sockaddr *disconnectedPlayer);
void handle_player_timeout(t_game *game);

#endif
