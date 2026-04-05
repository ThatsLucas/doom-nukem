/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:53:36 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/05 17:22:19 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "Game.h"

void	events_handler(t_game *game);
void	ply_movements(int key, t_ply *ply, t_game *game);
void	ply_directions(int key, t_ply *ply);

#endif
