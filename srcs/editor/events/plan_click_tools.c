/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_click_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:00:11 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:00:11 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Slope tool, right click: cancel the current slope or remove a slope arrow */
int	click_remove_slope(t_game *game, SDL_Event *e)
{
	t_editor_properties	*props = &game->editor->properties;
	t_vect2				click_pos;

	if (props->slope_step == 1)
	{
		props->slope_step = 0;
		return (1);
	}
	click_pos = pixels_to_pos(game->editor, (float)e->button.x, (float)e->button.y);
	for (int i = 0; i < game->editor->map->num_sectors; i++)
	{
		t_sector *s = &game->editor->map->sectors[i];
		if (s->has_floor_arrow && dist_vect(click_pos, s->floor_arrow_base) < 0.1f)
		{
			s->floor_plane = (t_plane){0.0f, 0.0f, 1.0f, s->floor_plane.d};
			s->has_floor_arrow = 0;
			return (1);
		}
		if (s->has_ceil_arrow && dist_vect(click_pos, s->ceil_arrow_base) < 0.1f)
		{
			s->ceil_plane = (t_plane){0.0f, 0.0f, 1.0f, s->ceil_plane.d};
			s->has_ceil_arrow = 0;
			return (1);
		}
	}
	return (1);
}

/*
	Entity tool, right click: cancel the current entity or remove a decal / entity.
	Returns 0 if nothing was removed, so the click falls back to the eraser.
*/
int	click_remove_entity(t_game *game, SDL_Event *e)
{
	t_vect2	click_pos;

	if (game->editor->entity_step == 1)
	{
		game->editor->entity_step = 0;
		return (1);
	}
	click_pos = pixels_to_pos(game->editor, (float)e->motion.x, (float)e->motion.y);
	if (suppress_decal(game, click_pos))
		return (1);
	for (int i = 0; i < game->editor->map->num_entities; i++)
	{
		t_map_ent *ent = &game->editor->map->entities[i];
		if (dist_vect(click_pos, ent->pos) < 0.1f)
		{
			ft_memmove(ent, ent + 1, sizeof(t_map_ent) * (game->editor->map->num_entities - i - 1));
			game->editor->map->num_entities--;
			return (1);
		}
	}
	return (0);
}

/* Right click with any tool: remove the vertice / wall under the cursor */
void	click_erase(t_game *game, SDL_Event *e)
{
	t_vect2	mousePos;

	game->editor->properties.draw_wall_active = 0;
	mousePos = pixels_to_pos(game->editor, e->motion.x, e->motion.y);
	suppress_vertice(game, mousePos.x, mousePos.y);
	suppress_wall(game, get_wall_index(game->editor->map, mousePos.x, mousePos.y));
	compute_sectors(game->editor->map);
}
