/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby_init_texts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:07:30 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:07:30 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"
#include "multiplayer/client.h"

/* Crée les textures des textes du salon. */
void init_lobby_texts(t_game *game)
{
    t_languages *lang = game->languages;
    SDL_Renderer *renderer = game->window->renderPTR;
    t_lobby *menu = &game->window->menus.lobby;

    menu->texts[0].size = 200;
    menu->texts[0].color = (SDL_Color){255, 255, 255, 255};
    create_text(&menu->texts[0], renderer, lang->lobby_solo, DNFONT);

    create_menu_button_texts(&menu->texts[1], renderer, lang->main_menu);
    create_menu_button_texts(&menu->texts[3], renderer, lang->level_one);
    create_menu_button_texts(&menu->texts[5], renderer, lang->level_two);
    create_menu_button_texts(&menu->texts[7], renderer, lang->level_three);
    create_menu_button_texts(&menu->texts[9], renderer, lang->multiplayer);

    menu->texts[11].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[11].size = 200;
    menu->texts[11].textHOffset = -10;
    create_text(&menu->texts[11], renderer, lang->lobby_multi, DNFONT);

    create_menu_button_texts(&menu->texts[12], renderer, lang->solo);

    menu->texts[14].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[14].size = 120;
    create_text(&menu->texts[14], renderer, lang->type_ip_addr, DNFONT);

    menu->texts[15].color = (SDL_Color){255, 255, 255, 255};
    menu->texts[15].size = 120;
    create_text(&menu->texts[15], renderer, lang->press_enter_to_confirm, DNFONT);

    create_menu_button_texts(&menu->texts[16], renderer, lang->host);
    create_menu_button_texts(&menu->texts[18], renderer, lang->join);
}
