/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:38:29 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/29 15:41:47 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/server.h"
#include "Game.h"

/*return la pos dans la table interne du joueur si trouve*/
int is_player_connected(t_game *game, struct sockaddr *client)
{
    for (int i = 0; i < 4; i++)
    {
        if (ft_memcmp(&game->serverStatus.address[i], client, sizeof(struct sockaddr)) == 0)
            return (i);
    }
    return (-1);
}

int add_new_player(t_game *game, struct sockaddr *newClient)
{
    t_server_udp_datas datas;

    if (!game || !newClient)
        return (-1);
    ft_bzero(&datas, sizeof(t_server_udp_datas));
    if (game->serverStatus.playerCount >= 4)
    {
        datas.state = 4; // game full
        send_to_client(&datas, newClient, game->serverStatus.serverSocket, -1);
        return (-2);
    }
    game->serverStatus.playerCount += 1;
    game->serverStatus.currentState = 1;
    int idx = game->serverStatus.playerCount - 1;
    ft_memcpy(&game->serverStatus.address[idx], newClient, sizeof(struct sockaddr));
    game->serverStatus.last_update[idx] = SDL_GetTicks64();
    game->serverStatus.players[idx][0] = 0;
    game->serverStatus.players[idx][1] = 0;
    game->serverStatus.player_angles[idx] = 0.0;
    datas.state = 1;
    datas.playerCount = game->serverStatus.playerCount;
    send_to_client(&datas, newClient, game->serverStatus.serverSocket, idx);
    return (idx);
}

void remove_player(t_game *game, struct sockaddr *disconnectedPlayer)
{
    if (!game || !disconnectedPlayer)
        return;
    for (int i = 0; i < 4; i++)
    {
        if (ft_memcmp(&game->serverStatus.address[i], disconnectedPlayer, sizeof(struct sockaddr)) == 0)
        {
            int count = game->serverStatus.playerCount;
            if (i < count - 1)
            {
                ft_memmove(&game->serverStatus.address[i],
                           &game->serverStatus.address[i + 1],
                           (count - i - 1) * sizeof(struct sockaddr));
                ft_memmove(&game->serverStatus.last_update[i],
                           &game->serverStatus.last_update[i + 1],
                           (count - i - 1) * sizeof(Uint64));
                ft_memmove(&game->serverStatus.players[i],
                           &game->serverStatus.players[i + 1],
                           (count - i - 1) * sizeof(game->serverStatus.players[0]));
                ft_memmove(&game->serverStatus.player_angles[i],
                           &game->serverStatus.player_angles[i + 1],
                           (count - i - 1) * sizeof(game->serverStatus.player_angles[0]));
            }
            game->serverStatus.playerCount -= 1;
            ft_bzero(&game->serverStatus.address[game->serverStatus.playerCount], sizeof(struct sockaddr));
            game->serverStatus.last_update[game->serverStatus.playerCount] = 0;
            game->serverStatus.players[game->serverStatus.playerCount][0] = 0;
            game->serverStatus.players[game->serverStatus.playerCount][1] = 0;
            game->serverStatus.player_angles[game->serverStatus.playerCount] = 0.0;
            return;
        }
    }
}

/*Envoie un msg a tout le monde excepte sauf int except*/
void broadcast_message(t_game *game, int except, t_server_udp_datas *datas)
{
    for (int i = 0; i < game->serverStatus.playerCount; i++)
    {
        if (i == except)
            continue;
        send_to_client(datas, &game->serverStatus.address[i], game->serverStatus.serverSocket, i);
    }
}

void broadcast_notifications(t_game *game, int except, char *str, int duration, int fontsize)
{
    t_server_udp_datas response;

    if (!str)
        return;
    ft_bzero(&response, sizeof(response));
    response.state = game->serverStatus.currentState;
    response.playerCount = game->serverStatus.playerCount;
    ft_memcpy(response.players, game->serverStatus.players, sizeof(game->serverStatus.players));
    ft_memcpy(response.player_angles, game->serverStatus.player_angles, sizeof(game->serverStatus.player_angles));
    response.is_notif = 1;
    response.notif_duration = duration;
    response.notif_font_size = fontsize;
    ft_strlcpy(response.notif_str, str, sizeof(response.notif_str));
    broadcast_message(game, except, &response);
}

void send_notifications(t_game *game, struct sockaddr *addr, char *str, int duration, int fontsize, int playerIndex)
{
    t_server_udp_datas response;

    if (!str)
        return;
    ft_bzero(&response, sizeof(response));
    response.state = game->serverStatus.currentState;
    response.playerCount = game->serverStatus.playerCount;
    ft_memcpy(response.players, game->serverStatus.players, sizeof(game->serverStatus.players));
    ft_memcpy(response.player_angles, game->serverStatus.player_angles, sizeof(game->serverStatus.player_angles));
    response.is_notif = 1;
    response.notif_duration = duration;
    response.notif_font_size = fontsize;
    ft_strlcpy(response.notif_str, str, sizeof(response.notif_str));
    send_to_client(&response, addr, game->serverStatus.serverSocket, playerIndex);
}

void send_default_info_response(t_game *game)
{
    t_server_udp_datas response;

    ft_bzero(&response, sizeof(response));
    response.state = game->serverStatus.currentState;
    response.level = game->serverStatus.currentLevel;
    response.playerCount = game->serverStatus.playerCount;
    ft_memcpy(response.players, game->serverStatus.players, sizeof(game->serverStatus.players));
    ft_memcpy(response.player_angles, game->serverStatus.player_angles, sizeof(game->serverStatus.player_angles));
    response.is_notif = 0;

    broadcast_message(game, -1, &response);
}