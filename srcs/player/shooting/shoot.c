/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:38:16 by edurance          #+#    #+#             */
/*   Updated: 2026/04/15 12:05:38 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

/* Update the frame and the ammo when a player is shooting -> a bouger quand yaura des ennemis*/
void	player_shoot(t_game *game)
{
	int				idx = game->ply->current_weap_index;
	t_weapon_type	type = game->ply->inventory.weapons[idx].type;
	t_weapon_3D		*w = &game->hud_cache.weapons_3D[type];

	if (w->is_firing)
		return ;
	if (game->ply->inventory.weapons[idx].ammo <= 0 && game->ply->inventory.weapons[idx].ammo != -1)
		return ;

	if (game->ply->inventory.weapons[idx].type != WEAP_FISTS)
		game->ply->inventory.weapons[idx].ammo -= 1;

	if (game->ply->inventory.weapons[idx].type == WEAP_ROCKET_LAUNCHER)
	{
		//float	tx = game->screenSize[0] / 2;
		//float	ty = game->screenSize[1] / 2;
		// spawn_rocket(game, tx, ty);
	}

	w->current_frame = 0;
	w->is_firing = 1;
	game->hud_cache.weap_tick = 0;
}
