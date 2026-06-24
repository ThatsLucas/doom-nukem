/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_place_slope.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 00:00:00 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/17 00:00:00 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static float	get_input_float(t_list *inputs, char *name)
{
	t_list			*current;
	t_text_input	*input;

	current = inputs;
	while (current)
	{
		input = (t_text_input *)current->content;
		if (!ft_strncmp(input->name, name, ft_strlen(name) + 1))
			return ((float)atof(input->text));
		current = current->next;
	}
	return (0.0f);
}

static t_plane	compute_slope_plane(t_vect2 base, t_vect2 tip, float intensity)
{
	float	dx;
	float	dy;
	float	l;
	float	A;
	float	B;

	dx = tip.x - base.x;
	dy = tip.y - base.y;
	l = sqrtf(dx * dx + dy * dy);
	if (l < 0.0001f)
		return ((t_plane){0.0f, 0.0f, 1.0f, 0.0f});
	A = intensity * (dx / l);
	B = intensity * (dy / l);
	return ((t_plane){-A, -B, 1.0f, -(A * base.x) - (B * base.y)});
}

void	editor_place_slope(t_game *game, int pixx, int pixy)
{
	t_editor_properties	*props;
	t_vect2				click_pos;
	int					sector_idx;
	t_sector			*sector;
	float				intensity;
	t_plane				plane;

	props = &game->editor->properties;
	if (pixx > game->editor->plan.size.w)
		return ;
	click_pos = pixels_to_pos(game->editor, (float)pixx, (float)pixy);

	if (props->slope_step == 0)
	{
		if (find_sector(game->editor->map, click_pos) < 0)
			return ;
		props->slope_base = click_pos;
		props->slope_step = 1;
		return ;
	}

	sector_idx = find_sector(game->editor->map, props->slope_base);
	props->slope_step = 0;
	if (sector_idx < 0)
		return ;
	sector = &game->editor->map->sectors[sector_idx];

	if (props->slope_fc == 0)
	{
		intensity = get_input_float(game->editor->text_inputs, "floor_intensity");
		plane = compute_slope_plane(props->slope_base, click_pos, intensity);
		sector->floor_plane = plane;
		sector->floor_arrow_base = props->slope_base;
		sector->floor_arrow_tip = click_pos;
		sector->has_floor_arrow = 1;
	}
	else
	{
		intensity = get_input_float(game->editor->text_inputs, "ceil_intensity");
		plane = compute_slope_plane(props->slope_base, click_pos, intensity);
		sector->ceil_plane = plane;
		sector->ceil_arrow_base = props->slope_base;
		sector->ceil_arrow_tip = click_pos;
		sector->has_ceil_arrow = 1;
	}
}
