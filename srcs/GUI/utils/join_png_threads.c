/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_png_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:14:19 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:14:19 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Window.h"
#include "GUI/GUI.h"

/* Attend le décodage des PNG et crée leurs textures. */
int	join_png_threads(pthread_t *threads, t_png **images, int count, SDL_Renderer *renderer)
{
	void	*ret = NULL;
	int		finalRet = 1;

	for (int i = 0; i < count; i++)
	{
		pthread_join(threads[i], &ret);

		if (!ret)
			finalRet = 0;
		else
			images[i]->texture =
				create_image(images[i], renderer);
	}
	return (finalRet);
}
