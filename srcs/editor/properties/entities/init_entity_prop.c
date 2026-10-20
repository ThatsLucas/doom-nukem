/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entity_prop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:59:47 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/07/15 18:00:01 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Editor.h"

static void	select_spawn(t_game *game)
{
	game->editor->selected_entity_type = 1;
	handle_entities(game, 0);
	return ;
}

static void	select_entity(t_game *game)
{
	game->editor->selected_entity_type = 2;
	handle_entities(game, 0);
	return ;
}

static void	select_item(t_game *game)
{
	game->editor->selected_entity_type = 3;
	handle_entities(game, 0);
	return ;
}

static void	select_props(t_game *game)
{
	game->editor->selected_entity_type = 4;
	handle_entities(game, 0);
	return ;
}

static void	add_entity_type_button(t_game *game, char *label, void (*callback)(t_game *), SDL_Rect dest)
{
	t_RGB	color = (t_RGB){171, 0, 186, 255};
	t_RGB	hover = (t_RGB){193, 115, 200, 255};
	t_font	*text = calloc(1, sizeof(t_font));

	text->color = (SDL_Color){255, 255, 255, 255};
	text->size = 24;
	create_text(text, game->window->renderPTR, label, "assets/fonts/MontserratBlack.ttf");
	create_button(&game->editor->buttons_entities, callback, dest, color, hover, text, text, -1);
}

void	init_entity_prop(t_game *game)
{
	SDL_Rect	dest;

	dest.w = 250;
	dest.h = 80;
	dest.x = 1555;
	dest.y = 555;
	add_entity_type_button(game, "Player Spawn", select_spawn, dest);
	dest.y += 100;
	add_entity_type_button(game, "Entities", select_entity, dest);
	dest.y += 100;
	add_entity_type_button(game, "Items", select_item, dest);
	dest.y += 100;
	add_entity_type_button(game, "Props", select_props, dest);

	game->editor->entity_text = ". . .";

	return ;
}
