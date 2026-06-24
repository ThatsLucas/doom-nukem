/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_to_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:05:07 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 11:58:16 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* plan_pixels to real position */
t_vect2	pixels_to_pos(t_editor *editor, float x, float y)
{
	t_vect2		res;

	res.x = (x - editor->plan.size.w / 2.0f) / editor->plan.case_size + editor->plan.center.x;
	res.y = (y - editor->plan.size.h / 2.0f) / editor->plan.case_size + editor->plan.center.y;

	return (res);
}
