/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_sent_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:09:17 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/28 15:14:58 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/client.h"
#include "Game.h"

void send_corresponding_datas_to_server(t_game *game)
{
    t_client_udp_datas datas;

    datas.level = game->current_level;
    datas.state = game->clientConnection.state;
    datas.x = game->ply->pos.x;
    datas.y = game->ply->pos.y;

    send_UDP_request(&datas, &game->clientConnection);
}
