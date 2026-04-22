/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pitch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 11:30:11 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/22 14:28:07 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"

/*
	Calcule le nouveau pitch
	1073741906 = UP
	1073741905 = DOWN
*/
void	ply_pitch(t_game *game, t_ply *ply, SDL_KeyboardEvent key)
{
	int	newpitch;
	int	step;

	step = 50;
	newpitch = ply->pitch;
	if (key.keysym.sym == 1073741906)
		newpitch = ply->pitch + step;
	if (key.keysym.sym == 1073741905)
		newpitch = ply->pitch - step;

	if (newpitch <= game->window->h && newpitch > -(game->window->h))
		ply->pitch = newpitch;
	return ;
}

