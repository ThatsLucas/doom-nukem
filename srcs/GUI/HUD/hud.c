/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:08:31 by edurance          #+#    #+#             */
/*   Updated: 2026/05/07 18:27:33 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "GUI/GUI.h"
#include "Game.h"

int	update_flashlight_battery(t_ply *p)
{
	t_tool	*flashlight = NULL;
	int i;

	for (i = 0; i < MAX_TOOLS; i++)
	{
		if (p->inventory.tools[i].type == TOOL_FLASHLIGHT)
		{
			flashlight = &p->inventory.tools[i];
			break ;
		}
	}

	static long	last_time = 0;
	static long	total_time = 0;

	if (!flashlight || !flashlight->using)
	{
		last_time = 0;
		return (i);
	}

	long	now = get_time_ms();
	if (last_time == 0)
		last_time = now;

	long	delta_time = now - last_time;

	total_time += delta_time;
	last_time = now;
	if (total_time >= 10000)
	{
		flashlight->data.battery -= 1;
		if (flashlight->data.battery <= 0)
			flashlight->data.battery = 0;
		total_time = 0;
		printf("new battery %d\n", p->inventory.tools[i].data.battery);
	}
	return (i);
}

void	display_battery(t_game *game)
{
	t_ply *p = game->ply;
	int index = update_flashlight_battery(p);

	draw_texture(1602, 800, 300, 74, game->window, game->hud_cache.battery[0]);

	for (int i = 0; i < p->inventory.tools[index].data.battery; i++)
	{
		draw_texture(1681 + i * (4 + 15), 825, 15, 24, game->window, game->hud_cache.battery[1]);
	}
}

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
	display_battery(game);
	//render_projectiles(game);
}
