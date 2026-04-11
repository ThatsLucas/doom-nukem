/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_side.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:14:03 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/10 15:20:05 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

/*
	Cote du mur par rapport au splitter:
	- 1 : Devant
	- 2 : Derriere
	- 3 : Coupe
*/
int	wall_side(t_wall *splitter, t_wall *wall)
{
	int		side1, side2;	// COte A et B du mur
	t_vect2	splitterEdge;	// Edge du splitter (end - start)

	splitterEdge = edge(splitter->start, splitter->end);
	side1 = vect2_product(splitterEdge, edge(splitter->start, wall->start));
	side2 = vect2_product(splitterEdge, edge(splitter->start, wall->end));

	if (side1 >= 0 && side2 >= 0)
		return (1); 	//devant
	if (side1 <= 0 && side2 <= 0)
		return (2);		//derriere
	return (3);			//coupe en deux
}
