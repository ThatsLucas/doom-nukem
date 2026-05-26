/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:16:04 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/26 14:49:21 by lle-duc          ###   ########.fr       */
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
    int state; // 1 lobby, 2 ingame, 3 game stop
    double players[10][2];

} t_server_udp_datas;

#endif
