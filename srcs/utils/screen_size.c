/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:47:43 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/08 11:21:50 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI.h"

void get_screen_size(int *w, int *h)
{
	SDL_DisplayMode DM;

	if (SDL_GetCurrentDisplayMode(0, &DM))
	{
		*w = 840;
		*h = 600;
    	printf("SDL error: %s\n", SDL_GetError());
    	return;
	}

	// *w = DM.w;
	// *h = DM.h;
	*w = 1250;
	*h = 800;
	return ;
}
