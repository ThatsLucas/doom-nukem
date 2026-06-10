/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jetpack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:26:07 by lle-duc           #+#    #+#             */
/*   Updated: 2026/06/10 16:42:00 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.h"

void use_jetpack(t_ply *ply)
{
    if (ply->inventory.jetpack->type != TOOL_JETPACK)
        if (ply->inventory.jetpack->data.fuel <= 0)
            return;
    float acceleration = 0.5f;
    ply->physic.velocity += acceleration;
}