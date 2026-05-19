/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:16:04 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/19 15:43:27 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_SHARED_H
#define MULTI_SHARED_H

// #include "Player.h"

#define PORT 2026

typedef struct s_udp_datas
{
    int state; // joining will be equal to the host addr, 1 is connected, 2 is leaving
    float x;
    float y;
    // t_ply players[10];

} t_udp_datas;

#endif
