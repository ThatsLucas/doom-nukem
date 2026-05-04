/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_zoom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:38:14 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/04 16:38:33 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

void	handle_zoom(t_editor *editor, SDL_MouseWheelEvent *wheel)
{
	if (wheel->mouseX >= editor->plan.size.w)
		return ;

	if (wheel->y < 0 && editor->plan.case_size > editor->plan.scale_min)
		editor->plan.case_size *= 0.9f;
	else if (wheel->y > 0 && editor->plan.case_size < editor->plan.scale_max)
		editor->plan.case_size *= 1.1f;

	return ;
}
