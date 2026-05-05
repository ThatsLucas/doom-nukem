/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:47:43 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 13:26:12 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"

void get_screen_size(int *w, int *h)
{
	SDL_DisplayMode DM;

	if (SDL_GetCurrentDisplayMode(0, &DM))
	{
		*w = 1920;
		*h = 1080;
		printf("SDL error: %s\n", SDL_GetError());
		return;
	}

	// *w = DM.w;
	// *h = DM.h;
	*w = 1600;
	*h = 800;
	return;
}
