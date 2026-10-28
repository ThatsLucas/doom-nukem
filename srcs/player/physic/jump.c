/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:10:27 by lle-duc           #+#    #+#             */
/*   Updated: 2026/06/29 14:07:25 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Player.h"

/* Fait sauter le joueur, ou utilise le jetpack en l’air. */
void player_jump(t_game *game, float dt)
{
    t_ply *ply = game->ply;
    if (!ply->physic.is_on_ground)
    {
        use_jetpack(ply, dt);
        return;
    }

    float acceleration = 2.0f;
    ply->physic.velocity += acceleration;
    ply->physic.is_on_ground = 0;
}