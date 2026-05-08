/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_add_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:31:55 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/08 11:17:01 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static int	get_alpha(t_game *game)
{
	t_list			*current = game->editor->text_inputs;
	t_text_input	*input;

	while (current)
	{
		input = (t_text_input *)current->content;
		if (!ft_strcmp(input->name, "walls_alpha"))
			return (SDL_clamp(ft_atoi(input->text), 0, 255));

		current = current->next;
	}

	return (255);
}

void	editor_add_wall(t_game *game, int v1, int v2)
{
	t_map	*map = game->editor->map;
	t_wall	*wall;

	if (map->num_walls == map->cap_walls)
		map_realloc(game, (void **)&map->walls, &map->cap_walls, sizeof(t_wall));

	wall = &map->walls[map->num_walls];
	wall->v1 = v1;
	wall->v2 = v2;
	wall->next_sector = -1;
	wall->alpha = get_alpha(game);

	// base pour linstant il faudra ajouter le reste: textures et tout

	map->num_walls++;

	return ;
}
