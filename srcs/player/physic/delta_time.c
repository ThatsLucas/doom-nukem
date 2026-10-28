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

/* Renvoie le temps écoulé en secondes depuis le dernier appel. */
float get_delta_time(t_ply *ply)
{
    Uint64 Curtime = SDL_GetTicks64();

    if (!ply->physic.last_time)
        ply->physic.last_time = Curtime;
    float deltaTime = (Curtime - ply->physic.last_time) / 1000.0f;
    ply->physic.last_time = Curtime;
    return (deltaTime);
}

/* Temps écoulé depuis *last en secondes, borné pour rester stable. */
float frame_delta(Uint64 *last)
{
    Uint64 now = SDL_GetTicks64();
    float dt;

    if (!*last)
        *last = now;
    dt = (now - *last) / 1000.0f;
    *last = now;
    if (dt > MAX_FRAME_DT)
        dt = MAX_FRAME_DT;
    return (dt);
}
