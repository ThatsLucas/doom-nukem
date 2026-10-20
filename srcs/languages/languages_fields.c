/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   languages_fields.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:20:14 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:20:14 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "languages/language.h"
#include "Game.h"

/* Liste les champs de traduction dans l’ordre des fichiers de langue. */
void get_language_fields(t_languages *l, char ***tab)
{
    char **fields[LANGUAGE_FIELDS] = {
        &l->loading,
        &l->play,
        &l->settings,
        &l->level_editor,
        &l->pick_a_key,
        &l->move_forward,
        &l->move_backward,
        &l->move_left,
        &l->move_right,
        &l->fov,
        &l->languages,
        &l->resolution,
        &l->display_mode,
        &l->fullscreen,
        &l->borderless,
        &l->windowed,
        &l->mouse_sensi,
        &l->main_menu,
        &l->lobby_solo,
        &l->level_one,
        &l->level_two,
        &l->level_three,
        &l->multiplayer,
        &l->lobby_multi,
        &l->solo,
        &l->cinematic_text_one,
        &l->cinematic_text_two,
        &l->cinematic_text_three,
        &l->cinematic_text_four,
        &l->cinematic_text_five,
        &l->cinematic_text_six,
        &l->cinematic_text_seven,
        &l->type_ip_addr,
        &l->press_enter_to_confirm,
        &l->host,
        &l->join,
        &l->cinematic_text_eight,
        &l->cinematic_text_nine,
        &l->cinematic_text_ten,
        &l->cinematic_text_eleven,
        &l->cinematic_text_twelve,
        &l->cinematic_text_thirteen,
        &l->cinematic_text_fourteen,
        &l->cinematic_text_fifteen,
        &l->cinematic_text_sixteen,
        &l->pause,
        &l->resume,
        &l->exit,
    };

    for (int i = 0; i < LANGUAGE_FIELDS; i++)
        tab[i] = fields[i];
}
