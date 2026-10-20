/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_click_select.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:00:11 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:00:11 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Met à jour le texte du champ de saisie sélectionné. */
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

/* Affiche les propriétés du mur sélectionné. */
static void	select_wall(t_game *game, int wall_idx)
{
	t_wall	*w = &game->editor->map->walls[wall_idx];
	char	buf[32];

	game->editor->properties.selected_wall = wall_idx;
	game->editor->properties.selected_property = 1;
	game->editor->properties.walls[0] = wall_idx >= 0 && w->tex_upper >= 0 ? game->editor->textures->textures[w->tex_upper] : NULL;
	game->editor->properties.walls[1] = wall_idx >= 0 && w->tex_mid >= 0 ? game->editor->textures->textures[w->tex_mid] : NULL;
	game->editor->properties.walls[2] = wall_idx >= 0 && w->tex_lower >= 0 ? game->editor->textures->textures[w->tex_lower] : NULL;
	ft_sputnbr(buf, (int)w->alpha, sizeof(buf));
	set_input_text(game->editor->text_inputs, "walls_alpha", buf);
}

/* Remplit les champs de saisie avec les propriétés du secteur. */
static void	fill_sector_inputs(t_list *inputs, t_sector *s)
{
	char	buf[32];

	ft_sputnbr(buf, (int)s->light_level, sizeof(buf));
	set_input_text(inputs, "sectors_light", buf);
	ft_sputfloat(buf, -s->floor_plane.d, sizeof(buf));
	set_input_text(inputs, "sectors_floor_z", buf);
	ft_sputfloat(buf, -s->ceil_plane.d, sizeof(buf));
	set_input_text(inputs, "sectors_ceil_z", buf);
	ft_sputnbr(buf, (int)s->direction, sizeof(buf));
	set_input_text(inputs, "sectors_direction", buf);
	ft_sputnbr(buf, (int)s->levelSize, sizeof(buf));
	set_input_text(inputs, "sectors_levelSize", buf);
}

/* Affiche les propriétés du secteur sélectionné. */
static void	select_sector(t_game *game, int sector_idx)
{
	t_sector	*s = &game->editor->map->sectors[sector_idx];

	game->editor->properties.selected_sector = sector_idx;
	game->editor->properties.selected_property = 3;
	game->editor->properties.sectors[0] = s->floor_tex >= 0 ? game->editor->textures->textures[s->floor_tex] : NULL;
	game->editor->properties.sectors[1] = s->ceil_tex >= 0 ? game->editor->textures->textures[s->ceil_tex] : NULL;
	game->editor->properties.sectors[2] = s->sky_tex >= 0 ? game->editor->textures->textures[s->sky_tex] : NULL;
	fill_sector_inputs(game->editor->text_inputs, s);
}

/* Sélectionne le mur ou le secteur cliqué. */
void	click_select(t_game *game, SDL_Event *e)
{
	t_vect2	mousePos;
	int		wall_idx;
	int		sector_idx;

	mousePos = pixels_to_pos(game->editor, e->motion.x, e->motion.y);
	wall_idx = get_wall_index(game->editor->map, mousePos.x, mousePos.y);
	if (wall_idx >= 0)
	{
		select_wall(game, wall_idx);
		return ;
	}
	sector_idx = find_sector(game->editor->map, mousePos);
	if (sector_idx >= 0)
		select_sector(game, sector_idx);
}
