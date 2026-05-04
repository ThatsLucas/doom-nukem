/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_to_pixels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:56:40 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/04 15:19:02 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

t_vect2	pos_to_pixels(t_editor *editor, float x, float y)
{
	t_vect2		res;

	res.x = (x - editor->plan.center.x) * editor->plan.case_size + editor->plan.size.w / 2.0f;
	res.y = (y - editor->plan.center.y) * editor->plan.case_size + editor->plan.size.h / 2.0f;

	return (res);
}
