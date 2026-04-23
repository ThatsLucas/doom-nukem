/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   language.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:51:02 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/22 17:33:26 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <unistd.h>

typedef struct s_game t_game;

typedef struct s_languages
{
    char *loading;
    char *play;
    char *settings;
    char *level_editor;
    char *pick_a_key;
    char *move_forward;
    char *move_backward;
    char *move_left;
    char *move_right;
    char *fov;
    char *languages;
    char *resolution;
    char *display_mode;
    char *borderless;
    char *fullscreen;
    char *windowed;
    char *main_menu;
} t_languages;

void parse_languages(t_game *game, int language);
void free_languages(t_game *game);

#endif