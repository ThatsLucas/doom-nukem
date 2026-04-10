/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HUD.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:14:14 by edurance          #+#    #+#             */
/*   Updated: 2026/04/10 10:37:38 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

#include <SDL_ttf.h>
#include <sys/time.h>

typedef struct	s_game t_game;
typedef struct	s_RGB t_RGB;

void	display_timer(t_game *game, int x, int y, int h, int w, t_RGB rgb);
void	display_hud(t_game *game);

#endif
