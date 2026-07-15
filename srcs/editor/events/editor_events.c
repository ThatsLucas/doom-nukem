/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:50:59 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/15 17:59:01 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Add text to the selected input if there is any */
static void handle_input(t_editor *editor, char *text)
{
	if (!editor->selected)
		return ;
	if (ft_strlen(editor->selected->text) + ft_strlen(text) < sizeof(editor->selected->text))
		ft_strlcat(editor->selected->text, text, sizeof(editor->selected->text));

	return ;
}

static float	get_input_float_ev(t_list *inputs, char *name)
{
	t_text_input	*inp;

	while (inputs)
	{
		inp = (t_text_input *)inputs->content;
		if (!ft_strncmp(inp->name, name, ft_strlen(name) + 1))
			return ((float)atof(inp->text));
		inputs = inputs->next;
	}
	return (0.0f);
}

static int	get_input_int_ev(t_list *inputs, char *name)
{
	t_text_input	*inp;

	while (inputs)
	{
		inp = (t_text_input *)inputs->content;
		if (!ft_strncmp(inp->name, name, ft_strlen(name) + 1))
			return (atoi(inp->text));
		inputs = inputs->next;
	}
	return (0);
}

static void	apply_wall_inputs(t_game *game)
{
	t_editor_properties	*props;
	int					alpha;

	props = &game->editor->properties;
	if (props->selected_property != 1 || props->selected_wall < 0
		|| props->selected_wall >= game->editor->map->num_walls)
		return ;
	alpha = get_input_int_ev(game->editor->text_inputs, "walls_alpha");
	if (alpha < 0)
		alpha = 0;
	if (alpha > 255)
		alpha = 255;
	game->editor->map->walls[props->selected_wall].alpha = (float)alpha;
}

static void	apply_sector_inputs(t_game *game)
{
	t_editor_properties	*props;
	t_sector			*sector;
	int					light;

	props = &game->editor->properties;
	if (props->selected_property != 3 || props->selected_sector < 0
		|| props->selected_sector >= game->editor->map->num_sectors)
		return ;
	sector = &game->editor->map->sectors[props->selected_sector];
	light = get_input_int_ev(game->editor->text_inputs, "sectors_light");
	if (light < 0)
		light = 0;
	if (light > 255)
		light = 255;
	sector->light_level = light;
	sector->floor_plane.d = -get_input_float_ev(game->editor->text_inputs, "sectors_floor_z");
	sector->ceil_plane.d = -get_input_float_ev(game->editor->text_inputs, "sectors_ceil_z");
	sector->direction = get_input_int_ev(game->editor->text_inputs, "sectors_direction");
	sector->levelSize = get_input_int_ev(game->editor->text_inputs, "sectors_levelSize");
}

static void handle_key(t_editor *editor, SDL_Keycode code, t_game *game)
{
	if (code == SDLK_ESCAPE)
		exit_game(game, NULL);

	if (code == SDLK_END)
		game->window->menus.current = 1;

	if (code == SDLK_RETURN || code == SDLK_KP_ENTER)
	{
		apply_sector_inputs(game);
		apply_wall_inputs(game);
	}

	if (editor->selected_tool == 3 && code == SDLK_LEFT)
		handle_entities(game, -1);

	if (editor->selected_tool == 3 && code == SDLK_RIGHT)
		handle_entities(game, 1);

	if (!editor->selected)
		return ;
	if (code == SDLK_BACKSPACE && ft_strlen(editor->selected->text))
		editor->selected->text[ft_strlen(editor->selected->text) - 1] = 0;

	return ;
}

static void	check_slop_button(t_game *game, int x, int y)
{
	SDL_Rect	box;

	box.h = 35; box.w = 80; box.x = 1639; box.y = 495;
	to_responsive(game->window, &box);

	if (x > box.x && x < box.x + box.w && y > box.y && y < box.y + box.h)
		game->editor->properties.slope_fc = game->editor->properties.slope_fc == 0 ? 1 : 0;

	return ;
}

/* Handle editor events (mouse, keys, etc.) */
void	editor_events(t_game *game)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
				exit_game(game, NULL);
				break ;

			case SDL_TEXTINPUT:
				handle_input(game->editor, e.text.text);
				break ;

			case SDL_KEYDOWN:
				handle_key(game->editor, e.key.keysym.sym, game);
				break ;

			case SDL_MOUSEBUTTONDOWN:
				get_selected_input(game, &game->editor->text_inputs, e.motion.x, e.motion.y);
				check_button_pressed(game, game->editor->buttons);
				if (game->editor->selected_tool == 3)
					check_button_pressed(game, game->editor->buttons_entities);
				if (!get_clicked_editor_button(game, e.motion.x, e.motion.y))
					plan_click(game, &e);
				get_clicked_texture(game, e.motion.x, e.motion.y);
				get_clicked_texture_button(game, e.motion.x, e.motion.y);
				check_slop_button(game, e.motion.x, e.motion.y);
				break ;

			case SDL_MOUSEBUTTONUP:
				plan_click(game, &e);
				break ;

			case SDL_MOUSEMOTION:
				plan_click(game, &e);
				break ;

			case SDL_MOUSEWHEEL:
				handle_zoom(game->editor, &e.wheel);
				break ;

			default:
				break ;
		}
	}

	return ;
}
