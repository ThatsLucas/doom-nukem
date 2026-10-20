/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 18:19:59 by lle-duc           #+#    #+#             */
/*   Updated: 2026/07/06 13:30:12 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

/* Ouvre le salon de jeu. */
static void draw_game_menu(t_game *game)
{
    game->window->menus.current = 3;
    SDL_SetRelativeMouseMode(SDL_FALSE);
}

/* Ouvre l’éditeur de carte. */
static void draw_editor(t_game *game)
{
    game->window->menus.current = -1;
    SDL_SetRelativeMouseMode(SDL_FALSE);
}

/* Initialise les images du menu principal. */
static int init_imgs(SDL_Renderer *renderer, t_main_menu *MainMenu)
{
    pthread_t threads[3];
    t_png *images[3] = {&MainMenu->background, &MainMenu->logo, &MainMenu->button};

    MainMenu->background.path = ft_strdup("assets/png/main_menu/background.png");
    MainMenu->logo.path = ft_strdup("assets/png/main_menu/logo.png");
    MainMenu->button.path = ft_strdup("assets/png/main_menu/button.png");
    for (int i = 0; i < 3; i++)
        pthread_create(&threads[i], NULL, process_png, images[i]);
    return (join_png_threads(threads, images, 3, renderer));
}

/* Initialise les textes des boutons du menu principal. */
static void init_button_texts(t_font *text, t_font *hover, SDL_Renderer *renderer, char *str, int hoffset)
{
    text->color = (SDL_Color){255, 255, 255, 255};
    text->size = 60;
    hover->color = (SDL_Color){221, 21, 0, 255};
    hover->size = 60;
    create_text(text, renderer, str, DNFONTOUTLINED);
    create_text(hover, renderer, str, DNFONT);
    text->textHOffset = hoffset;
    hover->textHOffset = hoffset;
}

/* Initialise le menu principal. */
int init_home_menu(t_game *game, t_WIN *win, SDL_Renderer *renderer, t_main_menu *MainMenu, int button_offset)
{
    if (!init_imgs(renderer, MainMenu))
        return (0);
    init_button_texts(&MainMenu->btn_one_text, &MainMenu->btn_one_text_hover, renderer, game->languages->play, -10);
    init_button_texts(&MainMenu->btn_two_text, &MainMenu->btn_two_text_hover, renderer, game->languages->settings, -10);
    init_button_texts(&MainMenu->btn_three_text, &MainMenu->btn_three_text_hover, renderer, game->languages->level_editor, -7);

    t_RGB color = {0, 255, 0, 0};
    SDL_Rect coords = {1920 / 2 - (MainMenu->button.w / 5) / 2, 450, MainMenu->button.w / 5, MainMenu->button.h / 5};
    create_button(&win->buttonList, &draw_game_menu, coords, color, color, &MainMenu->btn_one_text, &MainMenu->btn_one_text_hover, 1);
    coords.y += button_offset;
    create_button(&win->buttonList, &draw_settings_menu, coords, color, color, &MainMenu->btn_two_text, &MainMenu->btn_two_text_hover, 1);
    coords.y += button_offset + 5;
    create_button(&win->buttonList, &draw_editor, coords, color, color, &MainMenu->btn_three_text, &MainMenu->btn_three_text_hover, 1);
    return (1);
}

/* Affiche une image du menu à la position indiquée. */
static void draw_menu_image(t_game *game, SDL_Texture *texture, SDL_Rect dest)
{
    to_responsive(game->window, &dest);
    SDL_RenderCopy(game->window->renderPTR, texture, NULL, &dest);
}

/* Affiche le menu principal. */
void draw_main_menu(t_game *game)
{
    t_main_menu *menu = &game->window->menus.main;
    int button_offset = 150;
    int button_pos_h = 450;
    int winW = 1920;
    int winH = 1080;

    if (!menu->has_init)
        return;

    game->window->menus.current = 1;

    draw_menu_image(game, menu->background.texture, (SDL_Rect){0, 0, winW, winH});
    draw_menu_image(game, menu->logo.texture, (SDL_Rect){winW / 2 - 250, -20, 500, 500});
    for (int i = 0; i < 3; i++)
    {
        draw_menu_image(game, menu->button.texture, (SDL_Rect){winW / 2 - (menu->button.w / 5) / 2, button_pos_h, menu->button.w / 5, menu->button.h / 5});
        button_pos_h += button_offset;
    }

    display_buttons(game->window->buttonList, game, 1);
}
