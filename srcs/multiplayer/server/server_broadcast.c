/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_broadcast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:26:06 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:26:06 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/server.h"
#include "Game.h"

/* Remplit l’état de la partie commun à tous les paquets du serveur. */
void fill_game_state(t_server_udp_datas *response, t_game *game)
{
    response->state = game->serverStatus.currentState;
    response->level = game->serverStatus.currentLevel;
    response->playerCount = game->serverStatus.playerCount;
    ft_memcpy(response->players, game->serverStatus.players, sizeof(game->serverStatus.players));
    // double cote serveur, float dans le paquet : pas de memcpy direct
    for (int i = 0; i < 4; i++)
        response->player_angles[i] = (float)game->serverStatus.player_angles[i];
    ft_memcpy(response->player_hp, game->serverStatus.player_hp, sizeof(game->serverStatus.player_hp));
    response->entity_count = game->serverStatus.entity_count;
    ft_memcpy(response->entities, game->serverStatus.entities,
              sizeof(t_net_entity) * game->serverStatus.entity_count);
}

/* Envoie un message à tous les joueurs sauf un. */
void broadcast_message(t_game *game, int except, t_server_udp_datas *datas)
{
    for (int i = 0; i < game->serverStatus.playerCount; i++)
    {
        if (i == except)
            continue;
        datas->damage_total = game->serverStatus.damage_total[i];
        send_to_client(datas, &game->serverStatus.address[i], game->serverStatus.serverSocket, i);
    }
}

/* Envoie une notification à tous les joueurs sauf un. */
void broadcast_notifications(t_game *game, int except, char *str, int duration, int fontsize)
{
    t_server_udp_datas response;

    if (!str)
        return;
    ft_bzero(&response, sizeof(response));
    fill_game_state(&response, game);
    response.is_notif = 1;
    response.notif_duration = duration;
    response.notif_font_size = fontsize;
    ft_strlcpy(response.notif_str, str, sizeof(response.notif_str));
    broadcast_message(game, except, &response);
}

/* Envoie une notification à un joueur. */
void send_notifications(t_game *game, struct sockaddr *addr, char *str, int duration, int fontsize, int playerIndex)
{
    t_server_udp_datas response;

    if (!str)
        return;
    ft_bzero(&response, sizeof(response));
    fill_game_state(&response, game);
    if (playerIndex >= 0 && playerIndex < 4)
        response.damage_total = game->serverStatus.damage_total[playerIndex];
    response.is_notif = 1;
    response.notif_duration = duration;
    response.notif_font_size = fontsize;
    ft_strlcpy(response.notif_str, str, sizeof(response.notif_str));
    send_to_client(&response, addr, game->serverStatus.serverSocket, playerIndex);
}

/* Envoie l’état de la partie à tous les joueurs. */
void send_default_info_response(t_game *game)
{
    t_server_udp_datas response;

    ft_bzero(&response, sizeof(response));
    fill_game_state(&response, game);
    response.is_notif = 0;

    broadcast_message(game, -1, &response);
}