/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:08:31 by edurance          #+#    #+#             */
/*   Updated: 2026/04/12 13:51:38 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "GUI/GUI.h"
#include "Game.h"

void	display_hud(t_game *game)
{
	update_hud_anim(game);
	int	w, h = 0;
	get_screen_size(&w, &h);
	t_RGB	timer_color = {255, 255, 255, 255};
	t_RGB	crosshair_color = {255, 255, 255, 255};
	display_timer(game, 1762, 986, 120, 60, timer_color);
	display_module_health(game, 282, 908, 210, 70);
	display_module_tools(game, 600, 908, 210, 70);
	display_module_ammo(game, 1100, 908, 200, 70);
	display_module_weapons(game, 1400, 908, 240, 70);
	SDL_RenderFillCircle(game->window->renderPTR, game->screenSize[0] / 2, game->screenSize[1] / 2, 4, crosshair_color);
	display_player_module(game, 60, 900, 150, 160);
}
