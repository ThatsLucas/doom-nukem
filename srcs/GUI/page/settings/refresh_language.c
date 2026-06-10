/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_language.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:48:52 by lle-duc           #+#    #+#             */
/*   Updated: 2026/06/10 11:49:23 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

void refresh_main_menu_texts(t_game *game)
{
    t_main_menu *main = &game->window->menus.main;
    SDL_Renderer *renderer = game->window->renderPTR;

    destroy_text_texture(&main->btn_one_text);
    destroy_text_texture(&main->btn_one_text_hover);
    destroy_text_texture(&main->btn_two_text);
    destroy_text_texture(&main->btn_two_text_hover);
    destroy_text_texture(&main->btn_three_text);
    destroy_text_texture(&main->btn_three_text_hover);
    create_text(&main->btn_one_text, renderer, game->languages->play, DNFONTOUTLINED);
    create_text(&main->btn_one_text_hover, renderer, game->languages->play, DNFONT);
    create_text(&main->btn_two_text, renderer, game->languages->settings, DNFONTOUTLINED);
    create_text(&main->btn_two_text_hover, renderer, game->languages->settings, DNFONT);
    create_text(&main->btn_three_text, renderer, game->languages->level_editor, DNFONTOUTLINED);
    create_text(&main->btn_three_text_hover, renderer, game->languages->level_editor, DNFONT);
}

void refresh_settings_texts(t_game *game, t_settings_menu *menu)
{
    SDL_Renderer *renderer = game->window->renderPTR;

    destroy_text_texture(&menu->texts[0]);
    destroy_text_texture(&menu->texts[1]);
    destroy_text_texture(&menu->texts[2]);
    destroy_text_texture(&menu->texts[3]);
    destroy_text_texture(&menu->texts[4]);
    destroy_text_texture(&menu->texts[5]);
    destroy_text_texture(&menu->texts[6]);
    destroy_text_texture(&menu->texts[7]);
    destroy_text_texture(&menu->texts[8]);
    destroy_text_texture(&menu->texts[13]);
    destroy_text_texture(&menu->texts[14]);
    destroy_text_texture(&menu->texts[18]);
    destroy_text_texture(&menu->texts[19]);
    destroy_text_texture(&menu->texts[20]);
    destroy_text_texture(&menu->texts[21]);
    destroy_text_texture(&menu->texts[22]);
    create_text(&menu->texts[0], renderer, game->languages->settings, DNFONT);
    create_text(&menu->texts[1], renderer, game->languages->move_forward, DNFONT);
    create_text(&menu->texts[2], renderer, game->languages->move_backward, DNFONT);
    create_text(&menu->texts[3], renderer, game->languages->fov, DNFONT);
    create_text(&menu->texts[4], renderer, game->languages->languages, DNFONT);
    create_text(&menu->texts[5], renderer, game->languages->main_menu, DNFONT);
    create_text(&menu->texts[6], renderer, game->languages->main_menu, DNFONTOUTLINED);
    create_text(&menu->texts[7], renderer, game->languages->move_left, DNFONT);
    create_text(&menu->texts[8], renderer, game->languages->move_right, DNFONT);
    create_text(&menu->texts[13], renderer, game->languages->pick_a_key, DNFONT);
    create_text(&menu->texts[14], renderer, game->languages->resolution, DNFONT);
    create_text(&menu->texts[18], renderer, game->languages->display_mode, DNFONT);
    create_text(&menu->texts[19], renderer, game->languages->fullscreen, DNFONT);
    create_text(&menu->texts[20], renderer, game->languages->borderless, DNFONT);
    create_text(&menu->texts[21], renderer, game->languages->windowed, DNFONT);
    create_text(&menu->texts[22], renderer, game->languages->mouse_sensi, DNFONT);
}

void refresh_lobby_texts(t_game *game)
{
    t_lobby *menu = &game->window->menus.lobby;
    SDL_Renderer *renderer = game->window->renderPTR;

    destroy_text_texture(&menu->texts[0]);
    destroy_text_texture(&menu->texts[1]);
    destroy_text_texture(&menu->texts[2]);
    destroy_text_texture(&menu->texts[3]);
    destroy_text_texture(&menu->texts[4]);
    destroy_text_texture(&menu->texts[5]);
    destroy_text_texture(&menu->texts[6]);
    destroy_text_texture(&menu->texts[7]);
    destroy_text_texture(&menu->texts[8]);
    destroy_text_texture(&menu->texts[9]);
    destroy_text_texture(&menu->texts[10]);
    destroy_text_texture(&menu->texts[11]);
    destroy_text_texture(&menu->texts[12]);
    destroy_text_texture(&menu->texts[13]);
    destroy_text_texture(&menu->texts[14]);
    destroy_text_texture(&menu->texts[15]);
    destroy_text_texture(&menu->texts[16]);
    destroy_text_texture(&menu->texts[17]);
    destroy_text_texture(&menu->texts[18]);
    destroy_text_texture(&menu->texts[19]);

    create_text(&menu->texts[0], renderer, game->languages->lobby_solo, DNFONT);
    create_text(&menu->texts[1], renderer, game->languages->main_menu, DNFONT);
    create_text(&menu->texts[2], renderer, game->languages->main_menu, DNFONTOUTLINED);
    create_text(&menu->texts[3], renderer, game->languages->level_one, DNFONT);
    create_text(&menu->texts[4], renderer, game->languages->level_one, DNFONTOUTLINED);
    create_text(&menu->texts[5], renderer, game->languages->level_two, DNFONT);
    create_text(&menu->texts[6], renderer, game->languages->level_two, DNFONTOUTLINED);
    create_text(&menu->texts[7], renderer, game->languages->level_three, DNFONT);
    create_text(&menu->texts[8], renderer, game->languages->level_three, DNFONTOUTLINED);
    create_text(&menu->texts[9], renderer, game->languages->multiplayer, DNFONT);
    create_text(&menu->texts[10], renderer, game->languages->multiplayer, DNFONTOUTLINED);
    create_text(&menu->texts[11], renderer, game->languages->lobby_multi, DNFONT);
    create_text(&menu->texts[12], renderer, game->languages->solo, DNFONT);
    create_text(&menu->texts[13], renderer, game->languages->solo, DNFONTOUTLINED);
    create_text(&menu->texts[14], renderer, game->languages->type_ip_addr, DNFONTOUTLINED);
    create_text(&menu->texts[15], renderer, game->languages->press_enter_to_confirm, DNFONTOUTLINED);
    create_text(&menu->texts[16], renderer, game->languages->host, DNFONT);
    create_text(&menu->texts[17], renderer, game->languages->host, DNFONTOUTLINED);
    create_text(&menu->texts[18], renderer, game->languages->join, DNFONT);
    create_text(&menu->texts[19], renderer, game->languages->join, DNFONTOUTLINED);
}

void refresh_cinematics_texts(t_game *game)
{
    t_cinematic *menu = &game->window->menus.cinematic;
    SDL_Renderer *renderer = game->window->renderPTR;

    destroy_text_texture(&menu->texts[0]);
    destroy_text_texture(&menu->texts[1]);
    destroy_text_texture(&menu->texts[2]);
    destroy_text_texture(&menu->texts[3]);
    destroy_text_texture(&menu->texts[4]);
    destroy_text_texture(&menu->texts[5]);
    destroy_text_texture(&menu->texts[6]);
    create_text(&menu->texts[0], renderer, game->languages->cinematic_text_one, DNFONT);
    create_text(&menu->texts[1], renderer, game->languages->cinematic_text_two, DNFONT);
    create_text(&menu->texts[2], renderer, game->languages->cinematic_text_three, DNFONT);
    create_text(&menu->texts[3], renderer, game->languages->cinematic_text_four, DNFONT);
    create_text(&menu->texts[4], renderer, game->languages->cinematic_text_five, DNFONT);
    create_text(&menu->texts[5], renderer, game->languages->cinematic_text_six, DNFONT);
    create_text(&menu->texts[6], renderer, game->languages->cinematic_text_seven, DNFONT);
}