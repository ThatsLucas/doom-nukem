/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:33:17 by lucas             #+#    #+#             */
/*   Updated: 2026/10/20 13:54:01 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENUS_H
# define MENUS_H

# include "GUI/GUI.h"
# include "parser/PNG.h"
# include <SDL.h>

typedef struct s_main_menu
{
	t_png				background;
	t_png				logo;
	t_png				button;
	t_font				btn_one_text;
	t_font				btn_one_text_hover;
	t_font				btn_two_text;
	t_font				btn_two_text_hover;
	t_font				btn_three_text;
	t_font				btn_three_text_hover;
	int					has_init;
}						t_main_menu;

# define NOTIF_NOT_SHOWED 0
# define NOTIF_SPAWNING 1
# define NOTIF_DELETING 2

typedef struct s_notif
{
	char				*text;
	uint32_t			duration;		// in ms
	int					time_left;		// in ms
	int					state;			// 0 not showed yet, 1 moving to pos, 2 going back to no show
	int					w;
	int					h;
	t_font				font;
	SDL_Rect			coords;
}						t_notif;

typedef struct s_notif_buf
{
	t_notif				*notif;
	struct s_notif_buf	*next;
}						t_notif_buf;

typedef struct s_notif_ptr
{
	t_notif_buf			*notif_buf;
	t_png				Popup;
}						t_notif_ptr;

typedef struct s_settings_menu
{
	t_png				background;
	t_png				keys;
	t_png				separator;
	t_png				scroll;
	t_png				scroll_grab;
	t_font				texts[23];
	t_png				slider_bar;
	t_png				slider_grab;
	t_png				languages[5];
	int					isGrabbingSlider;
	int					isGrabbingSliderMouseSensi;
	int					isGrabbingScrollBar;
	int					scrollH;
	SDL_Rect			ViewPortCoords;
	SDL_Rect			MouseSensiCoords;
	SDL_Rect			languagesCoords[4];
	int					is_selecting_control;
	SDL_Rect			keysCoords[4];
	SDL_Rect			resolutionBtnsCoords[6];
}						t_settings_menu;

typedef struct s_lobby
{
	t_png				background;
	t_png				multi_background;
	t_png				button;
	t_png				playerImgs[5];
	SDL_Rect			playerBounds[5];			// zone opaque de chaque image (sans les marges transparentes)
	t_font				texts[20];
}						t_lobby;

# define CINEMATIC_ONE_DURATION 10000

typedef struct s_cinematic
{
	Uint64				cinematatic_duration;
	Uint64				cinematatic_begin_time;
	Uint64				last_time;
	// cinematique une
	t_png				bg_one;
	t_png				scientifics[5];
	float				scientificsXPos[5];
	t_png				smoke;
	float				smokeYPos;

	// cinematique deux
	t_png				bg_two;
	t_png				blue_light;
	float				blue_light_ratio;
	int					grow_order;

	// cinematique trois
	t_png				bg_three;
	t_png				lightning;
	t_png				eyes;
	t_png				boss;

	t_font				texts[16];
}						t_cinematic;

typedef struct s_pause
{
	t_font				texts[5];
}						t_pause;

typedef struct s_menus
{
	int					current;
	t_notif_ptr			notif;
	t_main_menu			main;
	t_settings_menu		settings;
	t_lobby				lobby;
	t_cinematic			cinematic;
	t_pause				pause;
}						t_menus;

/*MENUS*/
void					draw_current_menu(t_game *game);

/*MAIN MENU*/

void					draw_main_menu(t_game *game);
int						init_home_menu(t_game *game, t_WIN *win, SDL_Renderer *renderer, t_main_menu *MainMenu, int button_offset);
void					destroy_main_menu(t_main_menu *MainMenu);

/*NOTIFS*/
int						init_notif(t_png *notifImg, SDL_Renderer *renderer);
void					create_notif(t_notif_buf **notif_buf, char *str, int duration_ms, int fontSize);
void					display_notif(t_WIN *win, t_notif_buf **notif_buf);
void					destroy_notif_node(t_notif_buf **notif_buf);

/*SETTINGS*/
void					draw_settings_menu(t_game *game);
int						init_settings_menu(t_game *game, SDL_Renderer *renderer, t_settings_menu *SettingsMenu);
void					init_settings_texts(t_game *game);
void					handle_settings_click(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click);
void					handle_settings_released(t_settings_menu *menu);
int						handle_language_selection(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click);
int						handle_click_control(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas);
int						handle_resolution_click(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas);
int						handle_display_mode_click(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas);
int						grab_mouse_sensibility(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click);
int						grab_fov(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click);
int						grab_scroll(t_game *game, t_settings_menu *menu, SDL_MouseMotionEvent *MouseDatas, int click);
void					draw_texture(int x, int y, int w, int h, t_WIN *win, SDL_Texture *texture);
int						draw_FOV(int yPos, int *scrollH, t_game *game, t_settings_menu *menu);
int						draw_controls(int *scrollH, t_WIN *win, t_settings_menu *menu);
int						draw_section_header(int yPos, int *scrollH, t_WIN *win, t_font *title);
void					draw_pick_a_key(t_WIN *win);
int						handle_key_control_selected(t_game *game, int key);
void					draw_scroll_bar(t_game *game, t_settings_menu *menu);
void					handle_settings_scroll_mouse_wheel(t_game *game, t_settings_menu *menu, SDL_MouseWheelEvent *wheel);
int						draw_languages(int yPos, int *scrollH, t_game *game, t_settings_menu *menu);
int						draw_resolution(int yPos, int *scrollH, t_game *game, t_settings_menu *menu);
int						draw_display_mode(int yPos, int *scrollH, t_game *game, t_settings_menu *menu);
int						draw_mouse_sensibility(int yPos, int *scrollH, t_game *game, t_settings_menu *menu);
void					refresh_settings_texts(t_game *game, t_settings_menu *menu);
void					refresh_main_menu_texts(t_game *game);
void					refresh_lobby_texts(t_game *game);
void					refresh_cinematics_texts(t_game *game);
void					refresh_pause_menu_texts(t_game *game);

/* LOBBY */
void					draw_lobby_menu(t_game *game);
int						init_lobby_menu(t_game *game, SDL_Renderer *renderer, t_lobby *lobby);
void					init_lobby_texts(t_game *game);
void					draw_lobby_multiplayer_menu(t_game *game);
void					draw_enter_host_addr(t_game *game);
void					host_game(t_game *game);

/* CINEMATICS */
void					draw_cinematic_one(t_game *game);
int						init_cinematics_menus(t_game *game, SDL_Renderer *renderer, t_cinematic *cinematic);
float					cinematic_delta(t_cinematic *menu, Uint64 curTime);
void					update_light_pulse(t_cinematic *menu, float delta);
void					draw_cinematic_subtitle(t_cinematic *menu, t_WIN *win, int idx);
void					end_cinematic_if_over(t_game *game, t_cinematic *menu, Uint64 curTime);
void					draw_cinematic_two(t_game *game);
void					draw_cinematic_three(t_game *game);

/*LEVELS*/
void					load_level(t_game *game, int level);
void					start_level_1(t_game *game);
void					start_level_2(t_game *game);
void					start_level_3(t_game *game);
void					lobby_to_main_menu(t_game *game);
void					lobby_to_multi_lobby(t_game *game);
void					lobby_to_solo_lobby(t_game *game);

/*PAUSE*/
void					init_pause_texts(void *gameStruct);
void					draw_pause_menu(t_game *game);

#endif