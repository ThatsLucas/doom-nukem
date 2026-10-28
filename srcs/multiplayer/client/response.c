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

/* Reçoit une réponse du serveur. */
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

/* Affiche une notification envoyée par le serveur. */
void handle_server_notifications_request(t_server_udp_datas *datas, t_game *game)
{
    if (!datas->is_notif)
        return;
    create_notif(&game->window->menus.notif.notif_buf, datas->notif_str, datas->notif_duration, datas->notif_font_size);
}

/* Met à jour l’état de la partie reçu du serveur. */
void handle_game_state(t_server_udp_datas *datas, t_game *game)
{
    // on n'ecrase pas clientConnection.state : c'est l'etat qu'on envoie au serveur
    // (sinon le host repasse a 1 avant que le serveur ait vu sa demande de lancement)
    game->clientConnection.player_count = datas->playerCount;
    ft_memcpy(game->clientConnection.players, datas->players, sizeof(datas->players));
    // float cote serveur, double cote client : pas de memcpy direct
    for (int i = 0; i < 4; i++)
        game->clientConnection.player_angles[i] = datas->player_angles[i];
    ft_memcpy(game->clientConnection.player_hp, datas->player_hp, sizeof(datas->player_hp));

    // degats cumules envoyes par l'hote : on n'applique que la difference
    if (datas->damage_total > game->clientConnection.last_damage_total)
    {
        game->ply->hp -= datas->damage_total - game->clientConnection.last_damage_total;
        game->clientConnection.last_damage_total = datas->damage_total;
    }
    apply_server_entities(datas, game);

    // serveur encore au lobby alors qu'on lance la partie : il n'a juste pas encore recu notre paquet
    if (datas->state == 1 && game->clientConnection.state != 3)
        game->window->menus.current = 4;
    if (datas->state == 2)
    {
        int curMenu = game->window->menus.current;
        if ((curMenu >= 5 && curMenu <= 7) || curMenu == 0) // deja en cinematique ou en jeu
            return;
        load_level(game, datas->level);
    }
    if (datas->state == 4)
    {
        close_connection(game);
        create_notif(&game->window->menus.notif.notif_buf, "The game is full!", 5, 70);
    }
}
