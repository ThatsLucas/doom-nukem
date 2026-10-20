/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:19:25 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:41:30 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

/* Gère le choix de l’entité à placer. */
void	handle_entities(t_game *game, int x)
{
	t_editor	*editor			= game->editor;
	static char	*entities[9]	= {"Tung Sahur", "Captain", "Mr White", "Soldier", "Sergeant", "Monster", "Spider", "Dc Pouf", "Elephant"};
	static char	*items[6]		= {"Flashlight", "Key", "JetPack", "Pistol", "Shotgun", "Rocket Launcher"};
	static char	*props[4]		= {"Barrel", "Switch", "Switch_Key", "Window"};
	static int	idx = 0;

	if (!x)
		idx = 0;
	idx += x;

	if (editor->selected_entity_type == 1)
		editor->entity_text = "Player Spawn";
	if (editor->selected_entity_type == 2)
	{
		idx = SDL_clamp(idx, 0, 8);
		editor->entity_text = entities[idx];
	}
	if (editor->selected_entity_type == 3)
	{
		idx = SDL_clamp(idx, 0, 5);
		editor->entity_text = items[idx];
	}
	if (editor->selected_entity_type == 4)
	{
		idx = SDL_clamp(idx, 0, 3);
		editor->entity_text = props[idx];
	}
	editor->selected_entity = idx;

	return ;
}
