/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:36:28 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/09 15:37:27 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting.h"
#include "Game.h"

// calcule du score: |front - back| + cut * poids (poids = a quel point cut un mur est grave)
/*
	Renvoie le meilleur splitter pour le noeux BSP
*/
t_list	*best_splitter(t_list **first)
{
	int		front, back, cut;
	t_list	*best = NULL;
	int		best_score;

	for (t_list *x = *first; x; x = x->next)
	{
		front = 0, back = 0, cut = 0;
		for (t_list *y = *first; y; y = y->next)
		{
			if (x != y)
			{
				switch (wall_side(x->content, y->content))
				{
				case 1:
					front++;
					break;
				case 2:
					back++;
					break;
				case 3:
					cut++;
					break;
				}
			}
		}
		if (!best || best_score > abs(front - back) + cut * 4)
		{
			best_score = abs(front - back) + cut * 4;
			best = x;
		}
	}

	return (best);
}
