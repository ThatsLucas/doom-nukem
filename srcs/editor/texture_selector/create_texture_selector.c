/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture_selector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:18:09 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/05 20:42:01 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

void	create_texture_selector(t_game *game, SDL_Texture **addr, int *tex_index)
{
	game->editor->texture_selector.display = 1;
	game->editor->texture_selector.variable_to_set = addr;
	game->editor->texture_selector.index_to_set = tex_index;

	return ;
}
