/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HUD.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:14:14 by edurance          #+#    #+#             */
/*   Updated: 2026/05/07 15:52:31 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

#include <SDL_ttf.h>
#include <sys/time.h>
#include "inventory/Inventory.h"
#include "parser/PNG.h"

typedef struct	s_game t_game;
typedef struct	s_RGB t_RGB;

#define FRAME_COUNT 3
#define STATE_DEFAULT 0
#define STATE_INJURED 3
#define STATE_BLEEDING 6
#define STATE_DEAD 9

#define MINI_W 187
#define MINI_H 180
#define MINI_X 60
#define MINI_Y 895
#define MINI_CELLS 15

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
	long long			last_anim_time;
}				t_weapon_3D;

typedef struct	s_hud_cache
{
	SDL_Texture		*weapon_textures_2D[MAX_WEAPONS];
	t_weapon_3D		weapons_3D[MAX_WEAPONS];
	SDL_Texture		*tools_textures[MAX_TOOLS];
	SDL_Texture		*ply_textures[10];
	SDL_Texture		*bg_texture;
	TTF_Font		*text_font;
	TTF_Font		*number_font;

	long long ply_last_time;
	long long weap_last_time;
	int ply_frame;
}				t_hud_cache;

typedef enum	e_asset_type
{
	ASSET_WEAPON2D,
	ASSET_TOOL,
	ASSET_PLAYER,
}				t_asset_type;

typedef struct	s_load_job
{
	t_game			*game;
	char			*path;
	t_png			result;
	int				index;
	int				success;
	t_asset_type	type;
}				t_load_job;

/* Seperate modules */
void	display_timer(t_game *game, int x, int y, int h, int w, t_RGB rgb);
void	display_module_health(t_game *game, int x, int y, int w, int h);
void	display_module_tools(t_game *game, int x, int y, int w, int h);
void	display_module_ammo(t_game *game, int x, int y, int w, int h);
void	display_module_weapons(t_game *game, int x, int y, int w, int h);
void	display_player_module(t_game *game, int x, int y, int w, int h);
void	display_held_weapon(t_game *game);
void	display_crosshair(t_game *game, int x, int y, int size, int gap, t_RGB rgb);
void	display_hud_bg(t_game *game);
void	draw_minimap(SDL_Renderer *render, t_game *game);

/* General functions */
void		display_hud(t_game *game);
void		init_hud_cache(t_game *game);
void		free_hud_cache(t_game *game);
void		update_hud_anim(t_game *game);
long long	get_time_ms(void);

/* Minimap */
void	draw_minimap_walls(t_game *game, SDL_Renderer *render);
void	draw_player_minimap(SDL_Renderer *render, t_game *game, int size, t_RGB color);

#endif
