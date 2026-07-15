/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sector_property.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:57:27 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/08 14:26:41 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/*	Afficher le texte des propriété de sectors	*/
void	display_sector_property(t_game *game)
{
	draw_prop_text(game, "floor_texture", 1481, 463);
	draw_prop_text(game, "ceiling_texture", 1686, 463);

	draw_prop_text(game, "light_level", 1527, 617);
	draw_prop_text(game, "floor_z", 1527, 672);
	draw_prop_text(game, "ceil_z", 1527, 726);

	draw_prop_text(game, "sky_texture", 1470, 799);

	draw_prop_text(game, "direction", 1675, 835);
	draw_prop_text(game, "levelSize", 1675, 890);

	return ;
}
