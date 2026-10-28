/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   language.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:51:02 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/20 13:52:23 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LANGUAGES_H
# define LANGUAGES_H

# include <unistd.h>

typedef struct s_game	t_game;

# define LANGUAGE_FIELDS 49

typedef struct s_languages
{
	char				*loading;
	char				*play;
	char				*settings;
	char				*level_editor;
	char				*pick_a_key;
	char				*move_forward;
	char				*move_backward;
	char				*move_left;
	char				*move_right;
	char				*fov;
	char				*languages;
	char				*resolution;
	char				*display_mode;
	char				*borderless;
	char				*fullscreen;
	char				*windowed;
	char				*mouse_sensi;
	char				*main_menu;
	char				*lobby_solo;
	char				*level_one;
	char				*level_two;
	char				*level_three;
	char				*multiplayer;
	char				*lobby_multi;
	char				*solo;
	char				*cinematic_text_one;
	char				*cinematic_text_two;
	char				*cinematic_text_three;
	char				*cinematic_text_four;
	char				*cinematic_text_five;
	char				*cinematic_text_six;
	char				*cinematic_text_seven;
	char				*cinematic_text_eight;
	char				*cinematic_text_nine;
	char				*cinematic_text_ten;
	char				*cinematic_text_eleven;
	char				*cinematic_text_twelve;
	char				*cinematic_text_thirteen;
	char				*cinematic_text_fourteen;
	char				*cinematic_text_fifteen;
	char				*cinematic_text_sixteen;
	char				*type_ip_addr;
	char				*press_enter_to_confirm;
	char				*host;
	char				*join;
	char				*resume;
	char				*pause;
	char				*exit;
	char				*game_over;
}						t_languages;

void					parse_languages(t_game *game, int language);
void					free_languages(t_game *game);
void					get_language_fields(t_languages *l, char ***tab);

#endif