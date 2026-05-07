/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:08:31 by edurance          #+#    #+#             */
/*   Updated: 2026/05/07 12:07:37 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "GUI/GUI.h"
#include "Game.h"

/* General function to display all the HUD */
void	display_hud(t_game *game)
{
	t_RGB	timer_color = {255, 255, 255, 255};
	t_RGB	crosshair_color = {255, 255, 255, 255};

	int w = game->window->w;
	int h = game->window->h;

	update_hud_anim(game);
	// update_projectiles(game);

	display_crosshair(game, w / 2, h / 2, 15, 4, crosshair_color);
	display_held_weapon(game);
	display_hud_bg(game);
	display_timer(game, 1762, 955, 120, 60, timer_color);
	display_module_health(game, 325, 908, 210, 70);
	display_module_tools(game, 600, 908, 210, 70);
	display_module_ammo(game, 1095, 908, 200, 70);
	display_player_module(game, 900, 908, 120, 140);
	display_module_weapons(game, 1400, 908, 240, 70);
	draw_minimap(game->window->renderPTR, game);
	//render_projectiles(game);
}
