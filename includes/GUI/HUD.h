/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HUD.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:14:14 by edurance          #+#    #+#             */
/*   Updated: 2026/04/13 16:46:07 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

#include <SDL_ttf.h>
#include <sys/time.h>
#include "inventory/Inventory.h"

typedef struct	s_game t_game;
typedef struct	s_RGB t_RGB;

#define FRAME_COUNT 3
#define STATE_DEFAULT 0
#define STATE_INJURED 3
#define STATE_BLEEDING 6
#define STATE_DEAD 9

typedef enum	e_player_state
{
	PLY_DEFAULT,
	PLY_INJURED,
	PLY_BLEEDING,
	PLY_DEAD
}				t_player_state;

typedef struct	s_weapon_3D_frame
{
	SDL_Texture	*texture;
	SDL_Rect	dest;
}				t_weapon_3D_frame;

typedef struct	s_weapon_3D
{
	t_weapon_3D_frame	*frames;
	int					fire_rate;
	int					frame_count;
	int					current_frame;
	int					is_firing;
}				t_weapon_3D;

typedef struct	s_hud_cache
{
	SDL_Texture		*weapon_textures_2D[MAX_WEAPONS];
	t_weapon_3D		weapons_3D[MAX_WEAPONS];
	SDL_Texture		*tools_textures[MAX_TOOLS];
	SDL_Texture		*ply_textures[10];
	int				ply_frame;
	int				ply_tick;
	int				weap_tick;
	TTF_Font		*text_font;
	TTF_Font		*number_font;
}				t_hud_cache;

/* Seperate modules */
void	display_timer(t_game *game, int x, int y, int h, int w, t_RGB rgb);
void	display_module_health(t_game *game, int x, int y, int w, int h);
void	display_module_tools(t_game *game, int x, int y, int w, int h);
void	display_module_ammo(t_game *game, int x, int y, int w, int h);
void	display_module_weapons(t_game *game, int x, int y, int w, int h);
void	display_player_module(t_game *game, int x, int y, int w, int h);

/* General functions */
void	display_hud(t_game *game);
void	init_hud_cache(t_game *game);
void	free_hud_cache(t_game *game);
void	update_hud_anim(t_game *game);

void	player_shoot(t_game *game);

#endif
