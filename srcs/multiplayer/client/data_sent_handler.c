/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_sent_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:09:17 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/29 17:12:19 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/client.h"
#include "Game.h"

/* Envoie au serveur les données du joueur. */
void send_corresponding_datas_to_server(t_game *game)
{
    t_client_udp_datas datas;

    datas.level = game->current_level;
    if (game->window->menus.current == 0)
        datas.state = 3;
    else
        datas.state = game->clientConnection.state;
    datas.x = game->ply->pos.x;
    datas.y = game->ply->pos.y;
    // z = hauteur des yeux : on envoie les pieds, jamais sous le sol (accroupi)
    datas.z = game->ply->z - EYES_HEIGTH;
    if (datas.z < game->ply->floor_height)
        datas.z = game->ply->floor_height;

    datas.ang = atan2f(game->ply->dir.y, game->ply->dir.x);

    send_UDP_request(&datas, &game->clientConnection);
}
