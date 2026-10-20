/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_keys.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:00:46 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:00:46 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Ajoute le texte saisi au champ sélectionné. */
void	editor_text_input(t_editor *editor, char *text)
{
	if (!editor->selected)
		return ;
	if (ft_strlen(editor->selected->text) + ft_strlen(text) < sizeof(editor->selected->text))
		ft_strlcat(editor->selected->text, text, sizeof(editor->selected->text));

	return ;
}

/* Récupère la valeur décimale saisie dans l’éditeur. */
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

/* Récupère la valeur entière saisie dans l’éditeur. */
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

/* Applique les valeurs saisies aux propriétés du mur. */
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

/* Applique les valeurs saisies aux propriétés du secteur. */
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

/* Gère l’appui sur une touche dans l’éditeur. */
void	editor_key_down(t_editor *editor, SDL_Keycode code, t_game *game)
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
