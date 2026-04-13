/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:03:49 by edurance          #+#    #+#             */
/*   Updated: 2026/04/13 17:06:00 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
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

	w->current_frame = 0;
	w->is_firing = 1;
	game->hud_cache.weap_tick = 0;
}

/* Updates the current frame to make a sprite animation of the player and the weapons */
void	update_hud_anim(t_game *game)
{
	int				idx = game->ply->current_weap_index;
	t_weapon_type	type = game->ply->inventory.weapons[idx].type;
	t_weapon_3D		*w = &game->hud_cache.weapons_3D[type];

	game->hud_cache.weap_tick++;
	game->hud_cache.ply_tick++;
	if (game->hud_cache.ply_tick >= 220)
	{
		game->hud_cache.ply_tick = 0;
		game->hud_cache.ply_frame = (game->hud_cache.ply_frame + 1) % 3;
	}

	if (!w->is_firing)
		return ;

	if (game->hud_cache.weap_tick < w->fire_rate)
		return ;

	game->hud_cache.weap_tick = 0;
	w->current_frame++;

	if (w->current_frame >= w->frame_count)
	{
		w->current_frame = 0;
		w->is_firing = 0;
	}
}
