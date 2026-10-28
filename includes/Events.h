/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:53:36 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/02 11:29:22 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
#define EVENTS_H

#include "Game.h"

void	events_handler(t_game *game);
int		player_is_dead(t_game *game);
void	key_handler(t_game *game, SDL_KeyboardEvent key, SDL_Event *event);
void	ply_movements(t_ply *ply, t_game *game);
int		wall_collision(t_game *game, float next_x, float next_y);
void	ply_directions(t_ply *ply);
void	handle_mousewheel(t_game *game, SDL_MouseWheelEvent *wheel);
void	ply_pitch(t_game *game, t_ply *ply, SDL_KeyboardEvent key);
void	mouse_moves(int x, int y, t_game *game);
void	interactions(t_game *game);
void	player_shoot(t_game *game);

#endif
