/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:18:06 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/13 22:42:02 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

#include <SDL.h>
#include "Colors.h"

typedef struct	s_vect2
{
	float	x;
	float	y;
}			t_vect2;

typedef struct s_plane
{
	float	a;
	float	b;
	float	c;
	float	d;
}			t_plane;

typedef struct s_wall
{
	/* --- Géométrie (indices dans map->vertices) --- */
	int		v1;				/* premier vertex du segment */
	int		v2;				/* second vertex du segment */

	/* --- Connexion --- */
	int		next_sector;	/* -1 = solide, >= 0 = indice du voisin */

	/* --- Textures (indices dans map->textures, -1 = aucune) --- */
	int		tex_mid;		/* texture principale */
	int		tex_upper;		/* texture step du haut (portail) */
	int		tex_lower;		/* texture step du bas (portail) */

	/* --- Alignement de texture --- */
	float	u_offset;		/* décalage horizontal (le long du mur) */
	float	v_offset;		/* décalage vertical (haut en bas) */

	/* --- Transparence --- */
	float	alpha;			/* 1.0 = opaque, 0.0 = invisible */
}			t_wall;


typedef struct s_sector
{
	/* --- Murs (indices dans map->walls) --- */
	int		*walls;				/* tableau d'indices des murs du secteur */
	int		num_walls;			/* nombre de murs (== nombre de côtés) */

	/* --- Géométrie verticale --- */
	t_plane	floor_plane;		/* plan du sol (incliné ou plat) */
	t_plane	ceil_plane;			/* plan du plafond (incliné ou plat) */

	/* --- Textures (indices dans map->textures, -1 = aucune) --- */
	int		floor_tex;			/* texture du sol */
	int		ceil_tex;			/* texture du plafond */
	int		sky_tex;			/* -1 = pas de ciel, >= 0 = texture ciel  */

	/* --- Éclairage --- */
	int		light_level;		/* 0 (noir total) à 255 (plein jour) */
}			t_sector;

typedef struct s_ray
{
	t_vect2		dir;			/* direction du rayon (constante) */
	int			screen_x;		/* colonne de l'écran */
	int			y_top;			/* limite haute de pixels restants */
	int			y_bot;			/* limite basse de pixels restants */
}				t_ray;

typedef struct s_map
{
	/* --- Géométrie --- */
	t_vect2		*vertices;
	int			num_vertices;
	int			cap_vertices;	/* capacité allouée (pour realloc sans trop de cout) */

	t_wall		*walls;
	int			num_walls;
	int			cap_walls;

	t_sector	*sectors;
	int			num_sectors;
	int			cap_sectors;

	/* --- Ressources --- */
	SDL_Surface	*surface[4];
	int			num_textures;
	t_RGB		**text_colors;
}				t_map;

#endif
