/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:24:29 by lle-duc           #+#    #+#             */
/*   Updated: 2026/06/10 17:02:35 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.h"
#include "Game.h"

void apply_constant_forces_to_player(t_ply *ply)
{
    float delta_time = get_delta_time(ply);

    ply->physic.velocity -= ply->physic.gravity * delta_time;

    ply->z += ply->physic.velocity * delta_time;

    if (ply->z < ply->floor_height + EYES_HEIGTH)
    {
        ply->z = ply->floor_height + EYES_HEIGTH;
        ply->physic.velocity = 0.0f;
        ply->physic.is_on_ground = 1;
    }
    else if (ply->z > ply->ceiling_height)
    {
        ply->z = ply->ceiling_height;
        ply->physic.velocity = 0.0f;
    }
}