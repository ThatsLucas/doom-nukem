/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 11:43:32 by edurance          #+#    #+#             */
/*   Updated: 2026/06/08 11:55:53 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	interactions(t_game *game)
{
	t_ply	*ply = game->ply;

	if (ply->crosshair_target->type == ENTITY_PNJ && ply->crosshair_target->notif)
		create_notif(&game->window->PopupPtr.notif_buf, ply->crosshair_target->notif, 5, 40);
}
