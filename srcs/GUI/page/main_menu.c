/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 18:19:59 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/21 15:42:17 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"
// #include "../../../includes/GUI.h"

static void draw_game_menu(t_game *game)
{
    game->window->menus.current = 0;
}

static int init_imgs(SDL_Renderer *renderer, t_main_menu *MainMenu)
{
    pthread_t thread, thread2, thread3;
    void  *ret = NULL;
    int finalRet = 1;

    MainMenu->background.path = ft_strdup("assets/png/main_menu/background.png");
    MainMenu->logo.path = ft_strdup("assets/png/main_menu/logo.png");
    MainMenu->button.path = ft_strdup("assets/png/main_menu/button.png");
    pthread_create(&thread, NULL, process_png, &MainMenu->background);
    pthread_create(&thread2, NULL, process_png, &MainMenu->logo);
    pthread_create(&thread3, NULL, process_png, &MainMenu->button);
    
    pthread_join(thread, &ret);
    if (!ret)
        finalRet = 0;
    else
        MainMenu->background.texture = create_image(&MainMenu->background, renderer);

    pthread_join(thread2, &ret);
    if (!ret)
        finalRet = 0;
    else
        MainMenu->logo.texture = create_image(&MainMenu->logo, renderer);

    pthread_join(thread3, &ret);
    if (!ret)
        finalRet = 0;
    else
        MainMenu->button.texture = create_image(&MainMenu->button, renderer);
    return (finalRet);
}

int init_home_menu(t_WIN *win, SDL_Renderer *renderer, t_main_menu *MainMenu, int button_offset)
{
    if (!init_imgs(renderer, MainMenu))
        return (0);
    SDL_Color red = {221, 21, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    MainMenu->btn_one_text.color = white;
    MainMenu->btn_one_text.size = 60;

    MainMenu->btn_one_text_hover.color = red;
    MainMenu->btn_one_text_hover.size = 60;

    MainMenu->btn_two_text.color = white;
    MainMenu->btn_two_text.size = 60;

    MainMenu->btn_two_text_hover.color = red;
    MainMenu->btn_two_text_hover.size = 60;

    MainMenu->btn_three_text.color = white;
    MainMenu->btn_three_text.size = 60;

    MainMenu->btn_three_text_hover.color = red;
    MainMenu->btn_three_text_hover.size = 60;

    create_text(&MainMenu->btn_one_text, renderer, "PLAY", "assets/fonts/AmazDooMLeftOutline.ttf");
    create_text(&MainMenu->btn_one_text_hover, renderer, "PLAY", "assets/fonts/AmazDooMLeft.ttf");
    create_text(&MainMenu->btn_two_text, renderer, "SETTINGS", "assets/fonts/AmazDooMLeftOutline.ttf");
    create_text(&MainMenu->btn_two_text_hover, renderer, "SETTINGS", "assets/fonts/AmazDooMLeft.ttf");
    create_text(&MainMenu->btn_three_text, renderer, "LEVEL EDITOR", "assets/fonts/AmazDooMLeftOutline.ttf");
    create_text(&MainMenu->btn_three_text_hover, renderer, "LEVEL EDITOR", "assets/fonts/AmazDooMLeft.ttf");

    MainMenu->btn_one_text.textHOffset = -10;
    MainMenu->btn_one_text_hover.textHOffset = -10;
    MainMenu->btn_two_text.textHOffset = -10;
    MainMenu->btn_two_text_hover.textHOffset = -10;
    MainMenu->btn_three_text.textHOffset = -7;
    MainMenu->btn_three_text_hover.textHOffset = -7;
    
    t_RGB color = {0, 255, 0, 0}; 
    SDL_Rect coords = { 1920 / 2 - (MainMenu->button.w / 5) / 2, 450, MainMenu->button.w / 5, MainMenu->button.h / 5 };
    create_button(&win->buttonList, &draw_game_menu, coords, color, color, &MainMenu->btn_one_text, &MainMenu->btn_one_text_hover, 1);
    coords.y += button_offset;
    create_button(&win->buttonList, &draw_settings_menu, coords, color, color, &MainMenu->btn_two_text, &MainMenu->btn_two_text_hover, 1);
    coords.y += button_offset + 5;
    create_button(&win->buttonList, NULL, coords, color, color, &MainMenu->btn_three_text, &MainMenu->btn_three_text_hover, 1);
    return (1);
} 

void draw_main_menu(t_game *game)
{
    ft_printf("drawing main menu\n");
    t_main_menu *menu = &game->window->menus.main;
    int button_offset = 150;
    int button_pos_h = 450;

    if (!menu->has_init)
        return;
    
    game->window->menus.current = 1;
    int winW = 1920;
    int winH = 1080;

    // background
    SDL_Rect bg_dest = { 0, 0, winW, winH };
    to_responsive(game->window, &bg_dest);
	SDL_RenderCopy(game->window->renderPTR, menu->background.texture, NULL, &bg_dest);

    //logo
    SDL_Rect logo_dest = { winW / 2 - 250, -20, 500, 500};
    to_responsive(game->window, &logo_dest);
	SDL_RenderCopy(game->window->renderPTR, menu->logo.texture, NULL, &logo_dest);

    // //button
    SDL_Rect button_dest = { winW / 2 - (menu->button.w / 5) / 2, button_pos_h, menu->button.w / 5, menu->button.h / 5 };
    to_responsive(game->window, &button_dest);
	SDL_RenderCopy(game->window->renderPTR, menu->button.texture, NULL, &button_dest);

    button_pos_h += button_offset;
    SDL_Rect button2_dest = { winW / 2 - (menu->button.w / 5) / 2, button_pos_h, menu->button.w / 5, menu->button.h / 5 };
    to_responsive(game->window, &button2_dest);
	SDL_RenderCopy(game->window->renderPTR, menu->button.texture, NULL, &button2_dest);

    button_pos_h += button_offset;
    SDL_Rect button3_dest = { winW / 2 - (menu->button.w / 5) / 2, button_pos_h, menu->button.w / 5, menu->button.h / 5 };
    to_responsive(game->window, &button3_dest);
	SDL_RenderCopy(game->window->renderPTR, menu->button.texture, NULL, &button3_dest);

    display_buttons(game->window->buttonList, game, 1);
}