/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/05 11:42:00 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI.h"
#include "../libft/include/libft.h"

int main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS)) // a avoir au début du programme obligatoirement
	{
		ft_printf("SDL_Init Error: %s\n", SDL_GetError());
		return (1);
	}

	int w = 0, h = 0;

	get_screen_size(&w, &h);
	printf("Screen size = %d, %d\n", w, h);

	t_WIN *mainWindow = create_window("Doom Nukem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL );

	if (!mainWindow)
		return (1);
		
	t_RGB rgb;
	rgb.r = 51;
	rgb.g = 153;
	rgb.b = 255;
	rgb.alphaValue = 255;


	int			running = 1;
	SDL_Event	event;

	while (running)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEMOTION)
				printf("Mouse pos = %d, %d\n", event.motion.x, event.motion.y);
			if (event.type == SDL_QUIT)
				running = 0;
		}
			create_rectangle(mainWindow->renderPTR, 50, 50, 200, 200, rgb);
			create_rectangle(mainWindow->renderPTR, 650, 50, 200, 200, rgb);
			create_rectangle(mainWindow->renderPTR, 900/2 - 25, 225, 50, 50, rgb);
			create_rectangle(mainWindow->renderPTR, 50, 400, 800, 50, rgb);
			SDL_RenderDrawCircle(mainWindow->renderPTR, 850, 500, 20, rgb);
			SDL_RenderPresent(mainWindow->renderPTR);
	}

	SDL_DestroyRenderer(mainWindow->renderPTR);
	SDL_DestroyWindow(mainWindow->winPTR);
	SDL_Quit();
	return 0;
}
