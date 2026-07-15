/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:20:00 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/07 01:28:42 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.h"

/* Active/desactive le sprint (maintenir Shift) */
void player_run(t_ply *ply, int is_pressed)
{
    if (is_pressed && !ply->physic.is_crouching)
    {
        ply->physic.is_running = 1;
        return;
    }
    ply->physic.is_running = 0;
}
