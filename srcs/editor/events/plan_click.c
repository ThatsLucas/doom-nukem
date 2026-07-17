/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_click.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:37:26 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/17 13:05:39 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static void	set_input_text(t_list *inputs, char *name, char *value)
{
	t_text_input	*inp;

	while (inputs)
	{
		inp = (t_text_input *)inputs->content;
		if (!ft_strncmp(inp->name, name, ft_strlen(name) + 1))
		{
			ft_strlcpy(inp->text, value, sizeof(inp->text));
			return ;
		}
		inputs = inputs->next;
	}
}

/* Check if the texture_selector is displayed and the cursor was on it */
static int	check_selector_clicked(t_game *game, int x, int y)
{
	SDL_Rect	box = {.x = 680, .y = 525, .w = 750, .h = 400};

	if (!game->editor->texture_selector.display)
		return (0);

	to_responsive(game->window, &box);

	if (x <= box.x + box.w && x > box.x && y <= box.y + box.h && y > box.y)
		return (1);
	return (0);
}

static int	tool_click(t_game *game, SDL_Event *e)
{
	t_vect2				mousePos;
	t_vect2				click_pos;
	t_editor_properties	*props;

	props = &game->editor->properties;

	if (game->editor->selected_tool == 1 && e->button.button == SDL_BUTTON_LEFT)
	{
		editor_place_wall(game, e->motion.x, e->motion.y, e->button.button);
		return (1);
	}

	if (game->editor->selected_tool == 2 && e->button.button == SDL_BUTTON_LEFT)
	{
		editor_place_slope(game, e->motion.x, e->motion.y);
		return (1);
	}

	if (game->editor->selected_tool == 2 && e->button.button == SDL_BUTTON_RIGHT)
	{
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

	if (game->editor->selected_tool == 3 && e->button.button == SDL_BUTTON_RIGHT)
	{
		if (game->editor->entity_step == 1)
		{
			game->editor->entity_step = 0;
			return (1);
		}
		click_pos = pixels_to_pos(game->editor, (float)e->motion.x, (float)e->motion.y);
		for (int i = 0; i < game->editor->map->num_entities; i++)
		{
			t_map_ent *e = &game->editor->map->entities[i];
			if (dist_vect(click_pos, e->pos) < 0.1f)
			{
				ft_memmove(e, e + 1, sizeof(t_map_ent) * (game->editor->map->num_entities - i - 1));
				game->editor->map->num_entities--;
				return (1);
			}
		}
	}

	if (game->editor->selected_tool == 0 && e->button.button == SDL_BUTTON_LEFT)
	{
		mousePos = pixels_to_pos(game->editor, e->motion.x, e->motion.y);
		int wall_idx = get_wall_index(game->editor->map, mousePos.x, mousePos.y);
		if (wall_idx >= 0)
		{
			t_wall	*w = &game->editor->map->walls[wall_idx];
			char	buf[32];
			game->editor->properties.selected_wall = wall_idx;
			game->editor->properties.selected_property = 1;
			game->editor->properties.walls[0] = wall_idx >= 0 && w->tex_upper >= 0 ? game->editor->textures->textures[w->tex_upper] : NULL;
			game->editor->properties.walls[1] = wall_idx >= 0 && w->tex_mid >= 0 ? game->editor->textures->textures[w->tex_mid] : NULL;
			game->editor->properties.walls[2] = wall_idx >= 0 && w->tex_lower >= 0 ? game->editor->textures->textures[w->tex_lower] : NULL;
			snprintf(buf, sizeof(buf), "%d", (int)w->alpha);
			set_input_text(game->editor->text_inputs, "walls_alpha", buf);
		}
		else
		{
			int sector_idx = find_sector(game->editor->map, mousePos);
			if (sector_idx >= 0)
			{
				t_sector	*s = &game->editor->map->sectors[sector_idx];
				char		buf[32];
				game->editor->properties.selected_sector = sector_idx;
				game->editor->properties.selected_property = 3;
				game->editor->properties.sectors[0] = s->floor_tex >= 0 ? game->editor->textures->textures[s->floor_tex] : NULL;
				game->editor->properties.sectors[1] = s->ceil_tex >= 0 ? game->editor->textures->textures[s->ceil_tex] : NULL;
				game->editor->properties.sectors[2] = s->sky_tex >= 0 ? game->editor->textures->textures[s->sky_tex] : NULL;
				snprintf(buf, sizeof(buf), "%d", s->light_level);
				set_input_text(game->editor->text_inputs, "sectors_light", buf);
				snprintf(buf, sizeof(buf), "%.2f", -s->floor_plane.d);
				set_input_text(game->editor->text_inputs, "sectors_floor_z", buf);
				snprintf(buf, sizeof(buf), "%.2f", -s->ceil_plane.d);
				set_input_text(game->editor->text_inputs, "sectors_ceil_z", buf);
				snprintf(buf, sizeof(buf), "%d", s->direction);
				set_input_text(game->editor->text_inputs, "sectors_direction", buf);
				snprintf(buf, sizeof(buf), "%d", s->levelSize);
				set_input_text(game->editor->text_inputs, "sectors_levelSize", buf);
			}
		}
		return (1);
	}

	if (e->button.button == SDL_BUTTON_RIGHT)
	{
		game->editor->properties.draw_wall_active = 0;
		mousePos = pixels_to_pos(game->editor, e->motion.x, e->motion.y);
		suppress_vertice(game, mousePos.x, mousePos.y);
		suppress_wall(game, get_wall_index(game->editor->map, mousePos.x, mousePos.y));
		compute_sectors(game->editor->map);
		return (1);
	}


	return (0);
}

/* Manage when plan is clicked or mouse moved */
void	plan_click(t_game *game, SDL_Event *e)
{
	static int				plan_clicked = 0;
	static int				last_x = 0, last_y = 0;
	SDL_MouseMotionEvent	*motion = &e->motion;

	if (motion->x > game->editor->plan.size.w)
		return ;

	if (check_selector_clicked(game, motion->x, motion->y))
		return ;

	if (motion->type == SDL_MOUSEBUTTONDOWN && tool_click(game, e))
		return ;

	if (plan_clicked && motion->type == SDL_MOUSEBUTTONUP)
	{
		last_x = 0;
		last_y = 0;
		plan_clicked = 0;
	}
	else if (!plan_clicked && motion->type == SDL_MOUSEBUTTONDOWN)
		plan_clicked = 1;

	if (plan_clicked)
	{
		if (last_x)
			game->editor->plan.center.x += (last_x - motion->x) / (float)game->editor->plan.case_size;
		last_x = motion->x;
	}

	if (plan_clicked)
	{
		if (last_y)
			game->editor->plan.center.y += (last_y - motion->y) / (float)game->editor->plan.case_size;
		last_y = motion->y;
	}

	return ;
}
