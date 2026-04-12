/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 18:19:59 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/12 15:30:56 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
// #include "../../../includes/GUI.h"

static int init_home_menu(SDL_Renderer *renderer, t_png *background, t_png *logo, t_png *button)
{
    if(!process_png(background, "assets/png/main_menu/background.png"))
		return (0);
    background->texture = create_image(background, renderer);

    if(!process_png(logo, "assets/png/main_menu/logo.png"))
		return (0);
    logo->texture = create_image(logo, renderer);

    if(!process_png(button, "assets/png/main_menu/button.png"))
		return (0);
    button->texture = create_image(button, renderer);

    return (1);
} 

void draw_main_menu(t_game *game)
{
    static t_png background;
    static t_png logo;
    static t_png button;
    static int has_init = 0;
    
    if (!has_init)
        has_init = init_home_menu(game->window->renderPTR, &background, &logo, &button);
    
    int winW = game->window->w;
    int winH = game->window->h;

    //background
    SDL_Rect bg_dest = { 0, 0, winW, winH };
	SDL_RenderCopy(game->window->renderPTR, background.texture, NULL, &bg_dest);

    //logo
    SDL_Rect logo_dest = { winW / 2 - 250, -20, 500, 500};
	SDL_RenderCopy(game->window->renderPTR, logo.texture, NULL, &logo_dest);

    // //button
    SDL_Rect button_dest = { winW / 2 - (button.w / 5) / 2, 450, button.w / 5, button.h / 5 };
	SDL_RenderCopy(game->window->renderPTR, button.texture, NULL, &button_dest);

    SDL_Rect button2_dest = { winW / 2 - (button.w / 5) / 2, 600, button.w / 5, button.h / 5 };
	SDL_RenderCopy(game->window->renderPTR, button.texture, NULL, &button2_dest);

    SDL_Rect button3_dest = { winW / 2 - (button.w / 5) / 2, 750, button.w / 5, button.h / 5 };
	SDL_RenderCopy(game->window->renderPTR, button.texture, NULL, &button3_dest);
}