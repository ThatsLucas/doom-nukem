/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gauge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:15:21 by edurance          #+#    #+#             */
/*   Updated: 2026/07/15 17:35:52 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/HUD.h"
#include "Game.h"

static int	update_flashlight_battery(t_ply *p)
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
	if (total_time >= 3000)
	{
		flashlight->data.battery -= 1;
		if (flashlight->data.battery <= 0)
			flashlight->data.battery = 0;
		total_time = 0;
	}
	return (i);
}

static int	update_jetpack_fuel(t_ply *p)
{
	t_tool	*jetpack = NULL;
	int i;

	for (i = 0; i < MAX_TOOLS; i++)
	{
		if (p->inventory.tools[i].type == TOOL_JETPACK)
		{
			jetpack = &p->inventory.tools[i];
			break ;
		}
	}

	static long	last_time = 0;
	static long	total_time = 0;

	if (!jetpack || !jetpack->using)
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
	if (total_time >= 5000)
	{
		jetpack->data.fuel-= 1;
		if (jetpack->data.fuel <= 0)
			jetpack->data.fuel = 0;
		total_time = 0;
	}
	return (i);
}

void	display_gauge(t_game *game, int type)
{
	t_ply *p = game->ply;

	if (type == TOOL_FLASHLIGHT)
	{
		int index = update_flashlight_battery(p);

		draw_texture(1602, 724, 300, 74, game->window, game->hud_cache.battery[0]);

		for (int i = 0; i < p->inventory.tools[index].data.battery; i++)
			draw_texture(1681 + i * (4 + 15), 749, 15, 24, game->window, game->hud_cache.battery[1]);
	}
	else if (type == TOOL_JETPACK)
	{
		int index = update_jetpack_fuel(p);

		draw_texture(1576, 800, 326, 56, game->window, game->hud_cache.fuel[0]);

		for (int i = 0; i < p->inventory.tools[index].data.fuel; i++)
			draw_texture(1675 + i * (4 + 15), 816, 15, 24, game->window, game->hud_cache.fuel[1]);
	}
}
