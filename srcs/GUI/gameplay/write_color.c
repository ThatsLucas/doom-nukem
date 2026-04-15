/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:24:01 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/15 13:17:02 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"

/* Renvoie une couleur par rapport au facteur de lumiere */
Uint32  write_color(int r, int g, int b, int sect_light)
{
	if (sect_light < 0)
		return (0);
	if (sect_light >= 255)
		return ((r << 16) | (g << 8) | b);
	r = r * sect_light / 255;
	g = g * sect_light / 255;
	b = b * sect_light / 255;

	return ((r << 16) | (g << 8) | b);
}
