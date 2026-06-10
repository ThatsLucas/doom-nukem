/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:14:51 by lle-duc           #+#    #+#             */
/*   Updated: 2026/06/10 15:17:38 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.h"

float get_delta_time(t_ply *ply)
{
    Uint64 Curtime = SDL_GetTicks64();

    if (!ply->physic.last_time)
        ply->physic.last_time = Curtime;
    float deltaTime = (Curtime - ply->physic.last_time) / 1000.0f;
    ply->physic.last_time = Curtime;
    return (deltaTime);
}