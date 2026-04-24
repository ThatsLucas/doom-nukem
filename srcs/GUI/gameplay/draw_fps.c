/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:58:35 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/17 11:16:20 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "GUI/GUI.h"

/*Recuperer la timestamp actuelle en ms*/
static long get_timestamp(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

/*Afficher les FPS en haut a droite de l'ecran toutes les secondes*/
void display_fps(t_game *game)
{
	static int fps = 0;
	static long last_time = 0;
	long time;

	time = get_timestamp();
	if (!last_time)
	{
		last_time = time;
		return;
	}
	if (last_time + 1000 <= time)
	{
		if (game->fps)
			printf("%s\n", game->fps);
		free(game->fps);
		game->fps = NULL;
		game->fps = ft_itoa(fps);
		last_time = time;
		fps = 1;
	}
	else
		fps++;
	// if (game->fps)
	// 	printGAmeFPS;		TODO
	return;
}

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
