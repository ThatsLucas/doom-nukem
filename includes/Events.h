/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:53:36 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/08 12:22:06 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
#define EVENTS_H

#include "Game.h"

void	events_handler(t_game *game);
void	ply_movements(t_ply *ply, t_game *game);
void	ply_directions(t_ply *ply);
void	handle_mousewheel(t_game *game, SDL_MouseWheelEvent *wheel);
void	ply_pitch(t_game *game, t_ply *ply, SDL_KeyboardEvent key);
void	mouse_moves(int x, int y, t_game *game);
void	interactions(t_game *game);
void	player_shoot(t_game *game);

#endif
