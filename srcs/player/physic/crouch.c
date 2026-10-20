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

/* Accroupit ou relève le joueur. */
void player_crouch(t_ply *ply)
{
    if (!ply->physic.is_crouching)
    {
        ply->physic.speed = 0.01f;
        ply->physic.is_crouching = 1;
        return;
    }
    ply->physic.is_crouching = 0;
    ply->physic.speed = 0.03f;
}