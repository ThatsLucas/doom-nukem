/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_wall_property.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:25:17 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/29 23:03:19 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/*	Afficher le texte des propriété de murs	*/
void	display_walls_property(t_game *game)
{
	draw_prop_text(game, "texture_upp", 1493, 521);
	draw_prop_text(game, "texture_mid", 1493, 636);
	draw_prop_text(game, "texture_low", 1493, 751);

	draw_prop_text(game, "alpha", 1538, 886);

	return ;
}
