/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:04:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/08 13:18:45 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef struct	s_vect2
{
	float	x;
	float	y;
}			t_vect2;

t_vect2	edge(t_vect2 a, t_vect2 b);
int		inter_point(t_vect2	P, t_vect2 r, t_vect2 Q, t_vect2 s, t_vect2 *res);

#endif
