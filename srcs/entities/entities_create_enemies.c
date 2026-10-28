/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_create_enemies.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:35:44 by edurance          #+#    #+#             */
/*   Updated: 2026/08/11 14:18:04 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/GUI.h"

/* Crée un ennemi de type 1. */
void	create_enemy1(t_game *game, t_vect2 pos)
{
	t_entity	e = {0};

	init_fighter_base(game, &e, ENTITY_ENEMY, pos);
	e.attack_range = 3.0f;
	e.speed = 2.0f;
	e.hp = 100;
	e.damage = 15;
	e.fire_rate = 200;
	load_fighter_textures(game, &e, "assets/png/entities/enemies/enemy1/",
		(int [4]){400, 600, 200, 50});
	add_entity(game, &game->entities, e);
}

/* Crée un ennemi de type 2. */
void	create_enemy2(t_game *game, t_vect2 pos)
{
	t_entity	e = {0};

	init_fighter_base(game, &e, ENTITY_ENEMY, pos);
	e.attack_range = 4.0f;
	e.speed = 1.0f;
	e.hp = 130;
	e.damage = 5;
	e.fire_rate = 70;
	load_fighter_textures(game, &e, "assets/png/entities/enemies/enemy2/",
		(int [4]){690, 680, 700, 300});
	add_entity(game, &game->entities, e);
}

/* Crée un ennemi de type 3. */
void	create_enemy3(t_game *game, t_vect2 pos)
{
	t_entity	e = {0};

	init_fighter_base(game, &e, ENTITY_ENEMY, pos);
	e.attack_range = 4.0f;
	e.speed = 1.5f;
	e.hp = 250;
	e.damage = 10;
	e.fire_rate = 200;
	load_fighter_textures(game, &e, "assets/png/entities/enemies/enemy3/",
		(int [4]){400, 600, 500, 200});
	add_entity(game, &game->entities, e);
}
