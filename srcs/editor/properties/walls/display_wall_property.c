/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_wall_property.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:25:17 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:17:38 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/*	Afficher le texte des propriété de murs	*/
void	display_walls_property(t_game *game)
{
	SDL_Rect	background, toggle;

	draw_prop_text(game, "texture_upp", 1493, 521);
	draw_prop_text(game, "texture_mid", 1493, 636);
	draw_prop_text(game, "texture_low", 1493, 751);

	draw_prop_text(game, "alpha", 1538, 848);

	draw_prop_text(game, "collisions", 1501, 910);
	draw_prop_text(game, "on", 1684, 910);
	draw_prop_text(game, "off", 1820, 910);

	background.h = 35;
	background.w = 80;
	background.x = 1730;
	background.y = 911;
	to_responsive(game->window, &background);
	SDL_SetRenderDrawColor(game->window->renderPTR, 255, 255, 188, 255);
	SDL_RenderFillRect(game->window->renderPTR, &background);
	SDL_SetRenderDrawColor(game->window->renderPTR, 0, 0, 0, 255);
	SDL_RenderDrawRect(game->window->renderPTR, &background);

	toggle.h = 27;
	toggle.w = 36;
	toggle.x = 1734;
	toggle.y = 915;

	if (!game->editor->properties.wall_collisions)
		toggle.x = 1769;
	to_responsive(game->window, &toggle);
	SDL_RenderFillRect(game->window->renderPTR, &toggle);

	return ;
}
