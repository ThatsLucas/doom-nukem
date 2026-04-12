/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HUD.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:14:14 by edurance          #+#    #+#             */
/*   Updated: 2026/04/12 11:21:03 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

#include <SDL_ttf.h>
#include <sys/time.h>
#include "inventory/Inventory.h"

typedef struct	s_game t_game;
typedef struct	s_RGB t_RGB;

typedef struct	s_hud_cache
{
	SDL_Texture	*weapon_textures[MAX_WEAPONS];
	SDL_Texture	*tools_texture[MAX_TOOLS];
	TTF_Font	*text_font;
	TTF_Font	*number_font;
}				t_hud_cache;

void	display_timer(t_game *game, int x, int y, int h, int w, t_RGB rgb);
void	display_module_health(t_game *game, int x, int y, int w, int h);
void	display_module_tools(t_game *game, int x, int y, int w, int h);
void	display_module_ammo(t_game *game, int x, int y, int w, int h);
void	display_module_weapons(t_game *game, int x, int y, int w, int h);
void	display_hud(t_game *game);
void	init_hud_cache(t_game *game);
void	free_hud_cache(t_game *game);

#endif
