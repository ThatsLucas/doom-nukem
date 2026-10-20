/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pitch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 11:30:11 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 16:30:20 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"

/* Incline la vue avec les touches. */
void ply_pitch(t_game *game, t_ply *ply, SDL_KeyboardEvent key)
{
	int newpitch;
	int step;

	step = 50;
	newpitch = ply->pitch;
	if (key.keysym.sym == 1073741906)
		newpitch = ply->pitch + step;
	if (key.keysym.sym == 1073741905)
		newpitch = ply->pitch - step;

	if (newpitch <= game->screenSize[1] && newpitch > -(game->screenSize[1]))
		ply->pitch = newpitch;
	return;
}
