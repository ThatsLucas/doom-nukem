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

/* Crée le PNJ 1 et son message. */
void	create_pnj1(t_game *game, t_vect2 pos, t_vect2 dir)
{
	t_entity	e = {0};

	init_pnj_base(game, &e, pos, dir);
	e.notif = "The office upstairs opens the labs. The key is in containment!";
	load_entity_frames(game, &e, "assets/png/entities/pnj/tung/tung", 400, 600);
	add_entity(game, &game->entities, e);
}

/* Crée le PNJ 2 et son message. */
void	create_pnj2(t_game *game, t_vect2 pos, t_vect2 dir)
{
	t_entity	e = {0};

	init_pnj_base(game, &e, pos, dir);
	e.notif = "The control room opens the cave gate. It came through down there.";
	load_entity_frames(game, &e, "assets/png/entities/pnj/captain/captain", 350, 750);
	add_entity(game, &game->entities, e);
}

/* Crée le PNJ 3 et son message. */
void	create_pnj3(t_game *game, t_vect2 pos, t_vect2 dir)
{
	t_entity	e = {0};

	init_pnj_base(game, &e, pos, dir);
	e.notif = "It's behind that door. Raid the armory first... and end this.";
	load_entity_frames(game, &e, "assets/png/entities/pnj/walter/walter", 350, 650);
	add_entity(game, &game->entities, e);
}
