/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_create_pnjs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:40:40 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 11:40:40 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/GUI.h"

/* Tung Tung Tung Sahur */
void	create_pnj1(t_game *game, t_vect2 pos, t_vect2 dir)
{
	t_entity	e;

	init_pnj_base(game, &e, pos, dir);
	e.notif = "I am Tung Tung Sahur. Find the key, kill the enemies and get out of here !"; // a modif en fonction de l'histoire
	load_entity_frames(game, &e, "assets/png/entities/pnj/tung/tung", 400, 600);
	add_entity(game, &game->entities, e);
}

void	create_pnj2(t_game *game, t_vect2 pos, t_vect2 dir)
{
	t_entity	e;

	init_pnj_base(game, &e, pos, dir);
	e.notif = "Avengers... assemble!"; // a modif en fonction de l'histoire
	load_entity_frames(game, &e, "assets/png/entities/pnj/captain/captain", 350, 750);
	add_entity(game, &game->entities, e);
}

void	create_pnj3(t_game *game, t_vect2 pos, t_vect2 dir)
{
	t_entity	e;

	init_pnj_base(game, &e, pos, dir);
	e.notif = "I am the danger Skyler!"; // a modif en fonction de l'histoire
	load_entity_frames(game, &e, "assets/png/entities/pnj/walter/walter", 350, 650);
	add_entity(game, &game->entities, e);
}
