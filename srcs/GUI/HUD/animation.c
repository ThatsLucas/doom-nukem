/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:03:49 by edurance          #+#    #+#             */
/*   Updated: 2026/06/08 12:12:40 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"
#include "Game.h"

long long get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}

/* Updates the current frame to make a sprite animation of the player and the weapons */
void update_hud_anim(t_game *game)
{
	int idx = game->ply->current_weap_index;
	t_weapon_type type = game->ply->inventory.weapons[idx].type;
	t_weapon_3D *w = &game->hud_cache.weapons_3D[type];

	long long now = get_time_ms();

	if (now - game->hud_cache.ply_last_time >= 1000)
	{
		game->hud_cache.ply_last_time = now;
		game->hud_cache.ply_frame = (game->hud_cache.ply_frame + 1) % 3;
	}

	if (!w->is_firing)
		return;

	if (now - w->last_anim_time < w->fire_rate)
		return;

	w->last_anim_time = now;

	w->current_frame++;

	if (w->current_frame >= w->frame_count)
	{
		w->current_frame = 0;
		w->is_firing = 0;
	}
}
