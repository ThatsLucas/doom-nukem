/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:38:29 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/29 15:41:47 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/server.h"
#include "Game.h"

/* Remet à zéro les données de combat d’un emplacement joueur. */
static void reset_player_slot(t_game *game, int idx)
{
    game->serverStatus.player_hp[idx] = 0;
    game->serverStatus.damage_total[idx] = 0;
    game->serverStatus.hits_epoch[idx] = 0;
    ft_bzero(game->serverStatus.hits_seen[idx], sizeof(game->serverStatus.hits_seen[idx]));
}

/* Décale les données de combat quand le joueur i quitte la partie. */
static void shift_player_combat(t_game *game, int i, int count)
{
    int n = count - i - 1;

    ft_memmove(&game->serverStatus.player_hp[i], &game->serverStatus.player_hp[i + 1],
               n * sizeof(game->serverStatus.player_hp[0]));
    ft_memmove(&game->serverStatus.damage_total[i], &game->serverStatus.damage_total[i + 1],
               n * sizeof(game->serverStatus.damage_total[0]));
    ft_memmove(&game->serverStatus.hits_epoch[i], &game->serverStatus.hits_epoch[i + 1],
               n * sizeof(game->serverStatus.hits_epoch[0]));
    ft_memmove(&game->serverStatus.hits_seen[i], &game->serverStatus.hits_seen[i + 1],
               n * sizeof(game->serverStatus.hits_seen[0]));
}

/* Renvoie l’indice du joueur s’il est déjà connecté. */
int is_player_connected(t_game *game, struct sockaddr *client)
{
    for (int i = 0; i < 4; i++)
    {
        if (ft_memcmp(&game->serverStatus.address[i], client, sizeof(struct sockaddr)) == 0)
            return (i);
    }
    return (-1);
}

/* Ajoute un nouveau joueur au serveur. */
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
    if (game->serverStatus.playerCount == 1) // premier joueur : on repart du lobby
        game->serverStatus.currentState = 1;
    int idx = game->serverStatus.playerCount - 1;
    ft_memcpy(&game->serverStatus.address[idx], newClient, sizeof(struct sockaddr));
    game->serverStatus.last_update[idx] = SDL_GetTicks64();
    game->serverStatus.players[idx][0] = 0;
    game->serverStatus.players[idx][1] = 0;
    game->serverStatus.players[idx][2] = 0;
    game->serverStatus.player_angles[idx] = 0.0;
    reset_player_slot(game, idx);
    datas.state = 1;
    datas.playerCount = game->serverStatus.playerCount;
    send_to_client(&datas, newClient, game->serverStatus.serverSocket, idx);
    return (idx);
}

/* Retire un joueur du serveur. */
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
                shift_player_combat(game, i, count);
            }
            game->serverStatus.playerCount -= 1;
            ft_bzero(&game->serverStatus.address[game->serverStatus.playerCount], sizeof(struct sockaddr));
            game->serverStatus.last_update[game->serverStatus.playerCount] = 0;
            game->serverStatus.players[game->serverStatus.playerCount][0] = 0;
            game->serverStatus.players[game->serverStatus.playerCount][1] = 0;
            game->serverStatus.players[game->serverStatus.playerCount][2] = 0;
            game->serverStatus.player_angles[game->serverStatus.playerCount] = 0.0;
            reset_player_slot(game, game->serverStatus.playerCount);
            return;
        }
    }
}

/*double cote serveur, float dans le paquet : un memcpy deborderait sur playerIndex/is_notif*/
