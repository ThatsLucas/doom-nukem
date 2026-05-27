/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:16:04 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/27 16:00:40 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_SHARED_H
#define MULTI_SHARED_H

// #include "Player.h"

#define PORT 2026

typedef struct s_client_udp_datas
{
    int state; // joining will be 1, 2 is connected, 3 is leaving
    float x;
    float y;

    // t_ply players[10];

} t_client_udp_datas;

typedef struct s_server_udp_datas
{
    int state; // 1 lobby, 2 ingame, 3 game stop, 4 game full
    int playerCount;
    double players[4][2];

    // notifications handling
    int is_notif; // bool
    int notif_duration;
    int notif_font_size;
    char notif_str[256];
} t_server_udp_datas;

#endif
