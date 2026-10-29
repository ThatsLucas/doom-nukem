/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_language.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:48:52 by lle-duc           #+#    #+#             */
/*   Updated: 2026/07/06 14:55:46 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

/* Recrée la texture du texte après sa mise à jour. */
static void refresh_text(t_font *text, SDL_Renderer *renderer, char *str, char *font)
{
    destroy_text_texture(text);
    create_text(text, renderer, str, font);
}

/* Recrée les textes du menu principal dans la nouvelle langue. */
void refresh_main_menu_texts(t_game *game)
{
    t_main_menu *main = &game->window->menus.main;
    SDL_Renderer *renderer = game->window->renderPTR;

    refresh_text(&main->btn_one_text, renderer, game->languages->play, DNFONTOUTLINED);
    refresh_text(&main->btn_one_text_hover, renderer, game->languages->play, DNFONT);
    refresh_text(&main->btn_two_text, renderer, game->languages->settings, DNFONTOUTLINED);
    refresh_text(&main->btn_two_text_hover, renderer, game->languages->settings, DNFONT);
    refresh_text(&main->btn_three_text, renderer, game->languages->level_editor, DNFONTOUTLINED);
    refresh_text(&main->btn_three_text_hover, renderer, game->languages->level_editor, DNFONT);
}

/* Recrée les textes des paramètres dans la nouvelle langue. */
void refresh_settings_texts(t_game *game, t_settings_menu *menu)
{
    SDL_Renderer *renderer = game->window->renderPTR;

    refresh_text(&menu->texts[0], renderer, game->languages->settings, DNFONT);
    refresh_text(&menu->texts[1], renderer, game->languages->move_forward, DNFONT);
    refresh_text(&menu->texts[2], renderer, game->languages->move_backward, DNFONT);
    refresh_text(&menu->texts[3], renderer, game->languages->fov, DNFONT);
    refresh_text(&menu->texts[4], renderer, game->languages->languages, DNFONT);
    refresh_text(&menu->texts[5], renderer, game->languages->main_menu, DNFONT);
    refresh_text(&menu->texts[6], renderer, game->languages->main_menu, DNFONTOUTLINED);
    refresh_text(&menu->texts[7], renderer, game->languages->move_left, DNFONT);
    refresh_text(&menu->texts[8], renderer, game->languages->move_right, DNFONT);
    refresh_text(&menu->texts[13], renderer, game->languages->pick_a_key, DNFONT);
    refresh_text(&menu->texts[14], renderer, game->languages->resolution, DNFONT);
    refresh_text(&menu->texts[18], renderer, game->languages->display_mode, DNFONT);
    refresh_text(&menu->texts[19], renderer, game->languages->fullscreen, DNFONT);
    refresh_text(&menu->texts[20], renderer, game->languages->borderless, DNFONT);
    refresh_text(&menu->texts[21], renderer, game->languages->windowed, DNFONT);
    refresh_text(&menu->texts[22], renderer, game->languages->mouse_sensi, DNFONT);
}

/* Recrée les textes du salon dans la nouvelle langue. */
void refresh_lobby_texts(t_game *game)
{
    t_lobby *menu = &game->window->menus.lobby;
    SDL_Renderer *renderer = game->window->renderPTR;

    refresh_text(&menu->texts[0], renderer, game->languages->lobby_solo, DNFONT);
    refresh_text(&menu->texts[1], renderer, game->languages->main_menu, DNFONT);
    refresh_text(&menu->texts[2], renderer, game->languages->main_menu, DNFONTOUTLINED);
    refresh_text(&menu->texts[3], renderer, game->languages->level_one, DNFONT);
    refresh_text(&menu->texts[4], renderer, game->languages->level_one, DNFONTOUTLINED);
    refresh_text(&menu->texts[5], renderer, game->languages->level_two, DNFONT);
    refresh_text(&menu->texts[6], renderer, game->languages->level_two, DNFONTOUTLINED);
    refresh_text(&menu->texts[7], renderer, game->languages->level_three, DNFONT);
    refresh_text(&menu->texts[8], renderer, game->languages->level_three, DNFONTOUTLINED);
    refresh_text(&menu->texts[9], renderer, game->languages->multiplayer, DNFONT);
    refresh_text(&menu->texts[10], renderer, game->languages->multiplayer, DNFONTOUTLINED);
    refresh_text(&menu->texts[11], renderer, game->languages->lobby_multi, DNFONT);
    refresh_text(&menu->texts[12], renderer, game->languages->solo, DNFONT);
    refresh_text(&menu->texts[13], renderer, game->languages->solo, DNFONTOUTLINED);
    refresh_text(&menu->texts[14], renderer, game->languages->type_ip_addr, DNFONTOUTLINED);
    refresh_text(&menu->texts[15], renderer, game->languages->press_enter_to_confirm, DNFONTOUTLINED);
    refresh_text(&menu->texts[16], renderer, game->languages->host, DNFONT);
    refresh_text(&menu->texts[17], renderer, game->languages->host, DNFONTOUTLINED);
    refresh_text(&menu->texts[18], renderer, game->languages->join, DNFONT);
    refresh_text(&menu->texts[19], renderer, game->languages->join, DNFONTOUTLINED);
}

/* Recrée les textes des cinématiques dans la nouvelle langue. */
void refresh_cinematics_texts(t_game *game)
{
    t_cinematic *menu = &game->window->menus.cinematic;
    SDL_Renderer *renderer = game->window->renderPTR;

    refresh_text(&menu->texts[0], renderer, game->languages->cinematic_text_one, DNFONT);
    refresh_text(&menu->texts[1], renderer, game->languages->cinematic_text_two, DNFONT);
    refresh_text(&menu->texts[2], renderer, game->languages->cinematic_text_three, DNFONT);
    refresh_text(&menu->texts[3], renderer, game->languages->cinematic_text_four, DNFONT);
    refresh_text(&menu->texts[4], renderer, game->languages->cinematic_text_five, DNFONT);
    refresh_text(&menu->texts[5], renderer, game->languages->cinematic_text_six, DNFONT);
    refresh_text(&menu->texts[6], renderer, game->languages->cinematic_text_seven, DNFONT);
    refresh_text(&menu->texts[7], renderer, game->languages->cinematic_text_eight, DNFONT);
    refresh_text(&menu->texts[8], renderer, game->languages->cinematic_text_nine, DNFONT);
    refresh_text(&menu->texts[9], renderer, game->languages->cinematic_text_ten, DNFONT);
    refresh_text(&menu->texts[10], renderer, game->languages->cinematic_text_eleven, DNFONT);
    refresh_text(&menu->texts[11], renderer, game->languages->cinematic_text_twelve, DNFONT);
    refresh_text(&menu->texts[12], renderer, game->languages->cinematic_text_thirteen, DNFONT);
    refresh_text(&menu->texts[13], renderer, game->languages->cinematic_text_fourteen, DNFONT);
    refresh_text(&menu->texts[14], renderer, game->languages->cinematic_text_fifteen, DNFONT);
    refresh_text(&menu->texts[15], renderer, game->languages->cinematic_text_sixteen, DNFONT);
}

/* Recrée les textes du menu pause dans la nouvelle langue. */
void refresh_pause_menu_texts(t_game *game)
{
    t_pause *pause = &game->window->menus.pause;
    SDL_Renderer *renderer = game->window->renderPTR;

    refresh_text(&pause->texts[0], renderer, game->languages->pause, DNFONT);
    refresh_text(&pause->texts[1], renderer, game->languages->resume, DNFONTOUTLINED);
    refresh_text(&pause->texts[2], renderer, game->languages->resume, DNFONT);
    refresh_text(&pause->texts[3], renderer, game->languages->exit, DNFONTOUTLINED);
    refresh_text(&pause->texts[4], renderer, game->languages->exit, DNFONT);
}

/* Recrée le texte du game over dans la nouvelle langue. */
void refresh_game_over_texts(t_game *game)
{
    t_game_over *game_over = &game->window->menus.game_over;
    SDL_Renderer *renderer = game->window->renderPTR;

    refresh_text(&game_over->texts[0], renderer, game->languages->game_over, DNFONT);
}

/* Recrée les textes de l'écran de fin dans la nouvelle langue. */
void refresh_victory_texts(t_game *game)
{
    t_victory *victory = &game->window->menus.victory;
    SDL_Renderer *renderer = game->window->renderPTR;

    refresh_text(&victory->texts[0], renderer, game->languages->the_end, DNFONT);
    refresh_text(&victory->texts[1], renderer, game->languages->beat_the_game, DNFONT);
}
