/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:58:35 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/07 15:52:39 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/GUI.h"

/*
	Meme fonction que display_fps mais calcule a la frame pres pas a la seconde
	Resultat plus precis mais plus fluctant
*/
void display_fps_periodic(Uint64 start)
{
	Uint64 now = SDL_GetPerformanceCounter();
	double period = (double)(now - start) / SDL_GetPerformanceFrequency();

	double fps = 1.0 / period;
	printf("fps : %lf\n", fps);
	return;
}
