/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RGBtoSDLColor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:19:36 by edurance          #+#    #+#             */
/*   Updated: 2026/05/07 12:19:59 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

/* Convertit une couleur t_RGB en SDL_Color. */
SDL_Color	RGBtoSDLColor(t_RGB color)
{
	SDL_Color	res;

	res.a = color.alphaValue;
	res.r = color.r;
	res.g = color.g;
	res.b = color.b;

	return (res);
}
