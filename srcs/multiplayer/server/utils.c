/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:38:29 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/27 16:27:57 by lle-duc          ###   ########.fr       */
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
        send_to_client(&datas, newClient, game->serverStatus.serverSocket);
        return (-2);
    }
    game->serverStatus.playerCount += 1;
    int idx = game->serverStatus.playerCount - 1;
    ft_memcpy(&game->serverStatus.address[idx], newClient, sizeof(struct sockaddr));
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
            ft_memmove(&game->serverStatus.address[i],
                       &game->serverStatus.address[i + 1],
                       (game->serverStatus.playerCount - i - 1) * sizeof(struct sockaddr));

            game->serverStatus.playerCount -= 1;
            ft_bzero(&game->serverStatus.address[game->serverStatus.playerCount], sizeof(struct sockaddr));
        }
    }
}

/*Envoie un msg a tout le monde excepte sauf int except*/
void broadcast_message(t_game *game, int except, t_server_udp_datas *datas)
{
    ft_printf("Player count : %d\n", game->serverStatus.playerCount);
    for (int i = 0; i < game->serverStatus.playerCount; i++)
    {
        if (i == except)
            continue;
        ft_printf("Sent to player #%d\n", i);
        send_to_client(datas, &game->serverStatus.address[i], game->serverStatus.serverSocket);
    }
}

void broadcast_notifications(t_game *game, int except, char *str, int duration, int fontsize)
{
    t_server_udp_datas response;

    if (!str)
        return;
    response.state = game->serverStatus.currentState;
    response.playerCount = game->serverStatus.playerCount;
    ft_memcpy(response.players, game->serverStatus.players, sizeof(double[3][2]));
    response.is_notif = 1;
    response.notif_duration = duration;
    response.notif_font_size = fontsize;
    ft_strlcpy(response.notif_str, str, sizeof(response.notif_str));
    broadcast_message(game, except, &response);
    ft_printf("Sending notifications in broadcast mode\n");
}

void send_notifications(t_game *game, struct sockaddr *addr, char *str, int duration, int fontsize)
{
    t_server_udp_datas response;

    if (!str)
        return;
    response.state = game->serverStatus.currentState;
    response.playerCount = game->serverStatus.playerCount;
    ft_memcpy(response.players, game->serverStatus.players, sizeof(double[3][2]));
    response.is_notif = 1;
    response.notif_duration = duration;
    response.notif_font_size = fontsize;
    ft_strlcpy(response.notif_str, str, sizeof(response.notif_str));
    send_to_client(&response, addr, game->serverStatus.serverSocket);
}