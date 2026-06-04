/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:35:44 by edurance          #+#    #+#             */
/*   Updated: 2026/06/04 17:31:11 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

int	default_enemy(t_game *game, t_vect2 pos, char *idle_tex, char *shoot_tex, int w, int h)
{
	t_entity	e;

	e.type = ENTITY_ENEMY;
	e.status = E_STATUS_IDLE;
	e.attack_range = 3.0f;
	e.vision_angle = 360.0f;
	e.vision_range = 10.0f;
	e.speed = 2.0f;
	e.dir_x = 1.0f;
	e.dir_y = 1.0f;
	e.num_frames = 0;
	e.textures = 0;
	e.x = pos.x;
	e.y = pos.y;
	e.hp = 100;
	e.hitbox = 1;
	e.can_shoot = 0;
	e.last_shot_time = 0;
	e.damage = 15;
	e.fire_rate = 200;

	e.sector = find_sector(game->map, pos);
	if (e.sector == -1)
		return (0);
	e.z = get_plane_z(game->map->sectors[e.sector].floor_plane, pos.x, pos.y);

	t_png	idle, shoot;
	idle.w = w; shoot.w = w;
	idle.h = h; shoot.h = h;
	idle.path = ft_strdup(idle_tex); shoot.path = ft_strdup(shoot_tex);
	if (!process_png(&idle))
		exit_game(game, "Failed to load enemy");
	if (!process_png(&shoot))
		exit_game(game, "Failed to load enemy (shoot text)");

	if (!(e.texture = create_image(&idle, game->window->renderPTR))
		|| !(e.texture_shoot = create_image(&shoot, game->window->renderPTR)))
		exit_game(game, "Failed to create image enemy");

	add_entity(game, &game->entities, e);
	return (1);
}
