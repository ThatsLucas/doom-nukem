/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby_connect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:07:51 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:07:51 by aabouyaz         ###   ########.fr       */
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

/* Handles one event of the ip prompt, returns 1 when the prompt is closed */
static int handle_addr_event(t_game *game, char *str, size_t *cursor_pos, size_t text_size)
{
    SDL_Event event;

    if (!SDL_PollEvent(&event))
        return (0);
    if (event.type == SDL_TEXTINPUT)
        ft_strcat(str, event.text.text);
    if (event.type != SDL_KEYDOWN)
        return (0);
    if (event.key.keysym.sym == SDLK_BACKSPACE)
    {
        if (text_size > 0)
            str[text_size - 1] = '\0';
    }
    else if (event.key.keysym.sym == SDLK_LEFT)
    {
        if (*cursor_pos > 0)
            (*cursor_pos)--;
    }
    else if (event.key.keysym.sym == SDLK_RIGHT)
    {
        if (*cursor_pos < text_size)
            (*cursor_pos)++;
    }
    else if (event.key.keysym.sym == SDLK_RETURN)
    {
        SDL_StopTextInput();
        connect_to_lobby(game, str, 0);
        return (1);
    }
    else if (event.key.keysym.sym == SDLK_ESCAPE)
    {
        SDL_StopTextInput();
        return (1);
    }
    return (0);
}

/* Draws the typed ip and the two instruction texts */
static void draw_addr_texts(t_WIN *win, char *str, size_t text_size)
{
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

    SDL_RenderPresent(win->renderPTR);
    if (text.texture)
        SDL_DestroyTexture(text.texture);
}

/* Blocking prompt to type the host ip address */
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

        if (handle_addr_event(game, str, &cursor_pos, text_size))
            return ;
        draw_addr_texts(win, str, text_size);
    }
}
