/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/04 19:58:13 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI.h"

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO); // a avoir au début du programme obligatoirement

    
    int w = 0, h = 0;

    get_screen_size(&w, &h);
    printf("Screen size = %d, %d\n", w, h);

    t_WIN *mainWindow = create_window("Doom Nukem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_MAXIMIZED );
    
    if (!mainWindow)
        return (1);
        
    t_RGB rgb;
    rgb.r = 51;
    rgb.g = 153;
    rgb.b = 255;
    rgb.alphaValue = 255;

    create_rectangle(mainWindow->renderPTR, 50, 50, 200, 200, rgb);
    create_rectangle(mainWindow->renderPTR, 650, 50, 200, 200, rgb);
    create_rectangle(mainWindow->renderPTR, 900/2 - 25, 225, 50, 50, rgb);
    create_rectangle(mainWindow->renderPTR, 50, 400, 800, 50, rgb);
    SDL_RenderPresent(mainWindow->renderPTR);

    SDL_Event event;
    while (SDL_WaitEvent(&event))
    {
        if (event.type == SDL_MOUSEMOTION)
            printf("Mouse pos = %d, %d\n", event.motion.x, event.motion.y);
        if (event.type == SDL_QUIT)
            break;
    }
    
    SDL_DestroyRenderer(mainWindow->renderPTR);
    SDL_DestroyWindow(mainWindow->winPTR);
    return 0;
}