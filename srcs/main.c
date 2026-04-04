/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/04 17:23:30 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Window.h"
#include "../includes/GUI.h"

int main(void)
{
    t_WIN *mainWindow = create_window("Doom Nukem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 500, SDL_WINDOW_SHOWN );
    
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
    SDL_Delay(5000);
    SDL_DestroyRenderer(mainWindow->renderPTR);
    SDL_DestroyWindow(mainWindow->winPTR);
    return 0;
}