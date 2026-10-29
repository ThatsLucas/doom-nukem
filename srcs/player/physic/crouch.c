/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crouch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:55:48 by lle-duc           #+#    #+#             */
/*   Updated: 2026/06/10 18:06:17 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.h"

/* Accroupit le joueur tant que la touche est enfoncée. */
void player_crouch(t_ply *ply, int is_pressed)
{
    if (is_pressed)
    {
        ply->physic.speed = CROUCH_SPEED;
        ply->physic.is_crouching = 1;
        ply->physic.is_running = 0;
        return;
    }
    ply->physic.is_crouching = 0;
    ply->physic.speed = WALK_SPEED;
}