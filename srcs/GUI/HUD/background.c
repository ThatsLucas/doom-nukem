/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:35:42 by edurance          #+#    #+#             */
/*   Updated: 2026/06/08 12:13:10 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

/* To display the gray background for the hud */
void	display_hud_bg(t_game *game)
{
	draw_texture(0, 1080 - 190, 1920, 190, game->window, game->hud_cache.bg_texture);
}
