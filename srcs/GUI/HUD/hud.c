/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:08:31 by edurance          #+#    #+#             */
/*   Updated: 2026/04/17 11:54:24 by edurance         ###   ########.fr       */
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
	int	w, h = 0;
	get_screen_size(&w, &h);
	SDL_RenderFillCircle(game->window->renderPTR, game->screenSize[0] / 2, game->screenSize[1] / 2, 4, crosshair_color);
	
	update_hud_anim(game);
	// update_projectiles(game);
	
	display_module_weapons(game, 1400, 908, 240, 70);
	display_timer(game, 1762, 986, 120, 60, timer_color);
	display_module_health(game, 282, 908, 210, 70);
	display_module_tools(game, 600, 908, 210, 70);
	display_module_ammo(game, 1100, 908, 200, 70);
	display_player_module(game, 60, 908, 120, 140);
	render_projectiles(game);
}
