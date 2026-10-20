/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_create_bosses.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:40:40 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 11:40:40 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/GUI.h"

/* Spider */
void	create_boss1(t_game *game, t_vect2 pos)
{
	t_entity	e;

	init_fighter_base(game, &e, ENTITY_BOSS, pos);
	e.attack_range = 5.0f;
	e.speed = 3.0f;
	e.hp = 500;
	e.damage = 20;
	e.fire_rate = 130;
	load_fighter_textures(game, &e, "assets/png/entities/boss/boss1/",
		(int [4]){1500, 700, 1300, 400});
	add_entity(game, &game->entities, e);
}

/* Gros pouf */
void	create_boss2(t_game *game, t_vect2 pos)
{
	t_entity	e;

	init_fighter_base(game, &e, ENTITY_BOSS, pos);
	e.attack_range = 5.0f;
	e.speed = 2.0f;
	e.hp = 500;
	e.damage = 20;
	e.fire_rate = 300;
	load_fighter_textures(game, &e, "assets/png/entities/boss/boss2/",
		(int [4]){800, 750, 700, 200});
	add_entity(game, &game->entities, e);
}

/* Elephant */
void	create_boss3(t_game *game, t_vect2 pos)
{
	t_entity	e;

	init_fighter_base(game, &e, ENTITY_BOSS, pos);
	e.attack_range = 3.0f;
	e.speed = 1.0f;
	e.hp = 350;
	e.damage = 25;
	e.fire_rate = 300;
	load_fighter_textures(game, &e, "assets/png/entities/boss/boss3/",
		(int [4]){800, 750, 500, 300});
	add_entity(game, &game->entities, e);
}
