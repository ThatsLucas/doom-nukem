/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:16:04 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/18 13:25:04 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_SHARED_H
#define MULTI_SHARED_H

#include "Player.h"

#define PORT 2026

typedef struct s_udp_datas
{
    t_ply players[10];

} t_udp_datas;

#endif
