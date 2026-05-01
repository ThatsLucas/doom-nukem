/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rocket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:39:03 by edurance          #+#    #+#             */
/*   Updated: 2026/04/14 15:50:27 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	spawn_rocket(t_game *game, float tx, float ty)
{
	t_projectile	*proj;

	proj = calloc(1, sizeof(t_projectile));
	if (!proj)
		exit_game(game, "malloc error");

	proj->state = PROJ_FLYING;
	proj->x = game->screenSize[0] / 2 - 200;
	proj->y = game->screenSize[1] + 800;
	proj->target_x = tx;
	proj->target_y = ty;
	proj->speed = 3.0f;
	proj->expl_rate = 30;
	proj->start_dist = sqrtf((proj->target_x - proj->x) * (proj->target_x - proj->x) + (proj->target_y - proj->y) * (proj->target_y - proj->y));

	t_png	tmp;
	tmp.path = ft_strdup("assets/png/hud/projectiles/fireball_1.png");
	if (!process_png(&tmp))
		exit_game(game, "fireball process");

	proj->fly_texture = create_image(&tmp, game->window->renderPTR);
	proj->fly_dest = (SDL_Rect){0, 0, 436, 221};

	static char	*expl_paths[] = {
		"assets/png/hud/projectiles/explosion_1.png",
		"assets/png/hud/projectiles/explosion_2.png",
		"assets/png/hud/projectiles/explosion_3.png",
	};

	for (int i = 0; i < 3; i++)
	{
		t_png	etmp;
		etmp.path = ft_strdup(expl_paths[i]);
		if (!process_png(&etmp))
			exit_game(game, "process explosion");
		proj->expl_frames[i] = create_image(&etmp, game->window->renderPTR);
	}

	proj->next = game->projectiles;
	game->projectiles = proj;
}
