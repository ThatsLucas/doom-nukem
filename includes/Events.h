/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:53:36 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/09 12:33:35 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "Game.h"

void	events_handler(t_game *game);
void	ply_movements(t_ply *ply, t_game *game);
void	ply_directions(int key, t_ply *ply);
void	handle_mousewheel(t_game *game, SDL_MouseWheelEvent *wheel);

#endif
