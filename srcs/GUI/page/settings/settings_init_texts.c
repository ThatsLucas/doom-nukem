/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_init_texts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:09:07 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:09:07 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

void init_settings_texts(t_game *game)
{
    t_languages *lang = game->languages;
    SDL_Renderer *renderer = game->window->renderPTR;
    t_font *texts = game->window->menus.settings.texts;

    create_white_text(&texts[0], renderer, lang->settings, 80);
    create_white_text(&texts[1], renderer, lang->move_forward, 50);
    create_white_text(&texts[2], renderer, lang->move_backward, 50);
    create_white_text(&texts[3], renderer, lang->fov, 80);
    create_white_text(&texts[4], renderer, lang->languages, 80);
    create_menu_button_texts(&texts[5], renderer, lang->main_menu);
    create_white_text(&texts[7], renderer, lang->move_left, 50);
    create_white_text(&texts[8], renderer, lang->move_right, 50);

    /*CONTROLS*/
    create_white_text(&texts[9], renderer, (char *)&game->settings.move_forward, 80);
    create_white_text(&texts[10], renderer, (char *)&game->settings.move_backward, 80);
    create_white_text(&texts[11], renderer, (char *)&game->settings.move_left, 80);
    create_white_text(&texts[12], renderer, (char *)&game->settings.move_right, 80);
    create_white_text(&texts[13], renderer, lang->pick_a_key, 80);

    /*DISPLAY*/
    create_white_text(&texts[14], renderer, lang->resolution, 80);
    create_white_text(&texts[15], renderer, "1280 x 720", 70);
    create_white_text(&texts[16], renderer, "1920 x 1080", 70);
    create_white_text(&texts[17], renderer, "2560 x 1440", 70);
    create_white_text(&texts[18], renderer, lang->display_mode, 70);
    create_white_text(&texts[19], renderer, lang->fullscreen, 70);
    create_white_text(&texts[20], renderer, lang->borderless, 70);
    create_white_text(&texts[21], renderer, lang->windowed, 70);
    create_white_text(&texts[22], renderer, lang->mouse_sensi, 70);
}
