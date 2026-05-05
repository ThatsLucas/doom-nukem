/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:24:01 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/17 11:16:15 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"

/*
	Renvoie une couleur par rapport au facteur de lumiere 
	le bit shift de 8 est une division par 256 et pas 255 => résultat imparfait mais optimisé
*/
Uint32  write_color(int r, int g, int b, int sect_light)
{
	r = (r * sect_light) >> 8;
	g = (g * sect_light) >> 8;
	b = (b * sect_light) >> 8;
	return ((r << 16) | (g << 8) | b);
}
