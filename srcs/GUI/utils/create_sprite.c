/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 10:00:00 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/02 11:31:54 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"

/* Convertit un PNG décodé en texture logicielle. */
t_tex	png_to_tex(t_png *png)
{
	t_tex		tex;
	int			bpp;
	__uint8_t	*px;

	tex.w = (int)png->w;
	tex.h = (int)png->h;
	tex.colors = calloc((size_t)tex.w * tex.h, sizeof(t_RGB));
	if (!tex.colors)
		return (tex);
	bpp = png->IHDR.bytes_per_pixel;
	for (__uint32_t y = 0; y < png->h; y++)
	{
		for (__uint32_t x = 0; x < png->w; x++)
		{
			px = &png->buf[y][x * bpp];
			if (png->IHDR.color_type == 6)
				tex.colors[y * tex.w + x] = (t_RGB){px[0], px[1], px[2], px[3]};
			else if (png->IHDR.color_type == 2)
				tex.colors[y * tex.w + x] = (t_RGB){px[0], px[1], px[2], 255};
			else if (png->IHDR.color_type == 4)
				tex.colors[y * tex.w + x] = (t_RGB){px[0], px[0], px[0], px[1]};
			else
				tex.colors[y * tex.w + x] = (t_RGB){px[0], px[0], px[0], 255};
		}
	}
	return (tex);
}

/* Alloue une texture logicielle depuis un PNG et libère son tampon. */
t_tex	*create_sprite(t_png *png)
{
	t_tex	*tex;

	tex = malloc(sizeof(t_tex));
	if (tex)
	{
		*tex = png_to_tex(png);
		if (!tex->colors)
		{
			free(tex);
			tex = NULL;
		}
	}
	for (__uint32_t y = 0; y < png->h; y++)
		free(png->buf[y]);
	free(png->buf);
	png->buf = NULL;
	return (tex);
}
