/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:42:03 by lle-duc           #+#    #+#             */
/*   Updated: 2026/09/23 11:43:48 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

static void connect_to_lobby(t_game *game, char *ip, int is_host)
{
    if (game->clientConnection.con_socket != 0)
        return;
    t_client_udp_datas datas;
    ft_bzero(&datas, sizeof(t_client_udp_datas));
    game->clientConnection.state = 1;
    connect_player(&game->clientConnection, ip, &datas);
    game->clientConnection.last_update = SDL_GetTicks64();
    game->settings.multiplayer_enabled = 1;
    game->settings.is_host = is_host;
}

// ca va te co en local si le serveur existe deja
void host_game(t_game *game)
{
    connect_to_lobby(game, "127.0.0.1", 1);
}

void draw_enter_host_addr(t_game *game)
{
    char str[30];
    size_t cursor_pos = 0;
    t_WIN *win = game->window;
    ft_bzero(&str, sizeof(str));

    SDL_StartTextInput();
    while (1)
    {
        SDL_RenderClear(win->renderPTR);
        size_t text_size = ft_strlen(str);
        SDL_Rect coords = {0, 0, 1920, 1080};
        to_responsive(win, &coords);

        t_RGB black = {0, 0, 0, 200};
        create_rectangle(win->renderPTR, coords, black);

        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_TEXTINPUT:
                ft_strcat(str, event.text.text);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (text_size > 0)
                        str[text_size - 1] = '\0';
                }
                else if (event.key.keysym.sym == SDLK_LEFT)
                {
                    if (cursor_pos > 0)
                        cursor_pos--;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    if (cursor_pos < text_size)
                        cursor_pos++;
                }
                else if (event.key.keysym.sym == SDLK_RETURN)
                {
                    SDL_StopTextInput();
                    return connect_to_lobby(game, str, 0);
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_StopTextInput();
                    return;
                }
            }
        }
        t_font text;
        ft_bzero(&text, sizeof(t_font));
        if (text_size > 0)
        {
            text.color = (SDL_Color){255, 255, 255, 255};
            text.size = 120;
            create_text(&text, win->renderPTR, str, DNFONT);
            draw_texture(1920 / 2 - text.w / 2, 500, text.w, text.h, win, text.texture);
        }

        draw_texture(1920 / 2 - win->menus.lobby.texts[14].w / 2, 200, win->menus.lobby.texts[14].w, win->menus.lobby.texts[14].h, win, win->menus.lobby.texts[14].texture);
        draw_texture(1920 / 2 - win->menus.lobby.texts[15].w / 2, 800, win->menus.lobby.texts[15].w, win->menus.lobby.texts[15].h, win, win->menus.lobby.texts[15].texture);

        SDL_RenderPresent(game->window->renderPTR);
        if (text.texture)
            SDL_DestroyTexture(text.texture);
    }
}

static void draw_texts(t_game *game, t_lobby *menu)
{
    draw_texture(1920 / 2 - (menu->texts[11].w / 2), 50, menu->texts[11].w, menu->texts[11].h, game->window, menu->texts[11].texture);
}
void draw_lobby_multiplayer_menu(t_game *game)
{
    // SDL_Renderer *renderer = game->window->renderPTR;
    t_WIN *win = game->window;
    t_lobby *menu = &win->menus.lobby;

    game->window->menus.current = 4;

    draw_texture(0, 0, 1920, 1080, win, menu->multi_background.texture);
    draw_texture(20, 20, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture(400, 850, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture((1920 / 2 - (win->menus.main.button.w / 5 / 2)), 850, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture(1520 - win->menus.main.button.w / 5, 850, win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);

    draw_texture(400, (1000 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture((1920 / 2 - (win->menus.main.button.w / 5 / 2)), (1000 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);
    draw_texture(1520 - win->menus.main.button.w / 5, (1000 - (win->menus.main.button.h / 5 / 2)), win->menus.main.button.w / 5, win->menus.main.button.h / 5, win, win->menus.main.button.texture);

    int breathFrame = (SDL_GetTicks() / 1600) % 3;
    int pCount = game->clientConnection.player_count;
    if (pCount >= 1)
        draw_texture(1920 / 2 - (1024 / 8 / 2), 500, 1024 / 8, 1536 / 8, win, menu->playerImgs[breathFrame].texture);
    if (pCount >= 2)
        draw_texture(1920 / 2 - (1024 / 8 / 2) - 150, 500, 1024 / 8, 1536 / 8, win, menu->playerImgs[(breathFrame + 1) % 3].texture);
    if (pCount >= 3)
        draw_texture(1920 / 2 - (1024 / 8 / 2) + 150, 500, 1024 / 8, 1536 / 8, win, menu->playerImgs[(breathFrame + 2) % 3].texture);
    if (pCount >= 4)
        draw_texture(1920 / 2 - (1024 / 8 / 2) - 300, 500, 1024 / 8, 1536 / 8, win, menu->playerImgs[(breathFrame + 3) % 3].texture);

    draw_texts(game, menu);
    display_buttons(game->window->buttonList, game, 4);
}
