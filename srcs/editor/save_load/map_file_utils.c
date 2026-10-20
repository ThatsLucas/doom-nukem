/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:03:09 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:03:09 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Lit exactement size octets, sinon renvoie -1. */
int	read_full(int fd, void *buf, size_t size)
{
	ssize_t	r;

	if (size == 0)
		return (0);
	r = read(fd, buf, size);
	if (r < 0 || (size_t)r != size)
		return (-1);
	return (0);
}

/* Récupère le texte saisi pour le nom de la carte. */
char	*get_map_name_input(t_game *game)
{
	t_list			*current = game->editor->text_inputs;
	t_text_input	*input;

	while (current)
	{
		input = (t_text_input *)current->content;
		if (!ft_strcmp("mapName", input->name))
			return (input->text);
		current = current->next;
	}
	return (NULL);
}
