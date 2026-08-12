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

void	init_entity_prop(t_game *game)
{
	SDL_Rect	dest;
	t_RGB		color = (t_RGB){171, 0, 186, 255};
	t_RGB		hover = (t_RGB){193, 115, 200, 255};
	t_font		*player_spawn = calloc(1, sizeof(t_font));
	t_font		*entities = calloc(1, sizeof(t_font));
	t_font		*items = calloc(1, sizeof(t_font));
	t_font		*props = calloc(1, sizeof(t_font));

	dest.w = 250;
	dest.h = 80;
	dest.x = 1555;
	dest.y = 555;
	player_spawn->color = (SDL_Color){255, 255, 255, 255};
	player_spawn->size = 24;
	create_text(player_spawn, game->window->renderPTR, "Player Spawn", "assets/fonts/MontserratBlack.ttf");
	create_button(&game->editor->buttons_entities, select_spawn, dest, color, hover, player_spawn, player_spawn, -1);

	dest.y += 100;
	entities->color = (SDL_Color){255, 255, 255, 255};
	entities->size = 24;
	create_text(entities, game->window->renderPTR, "Entities", "assets/fonts/MontserratBlack.ttf");
	create_button(&game->editor->buttons_entities, select_entity, dest, color, hover, entities, entities, -1);

	dest.y += 100;
	items->color = (SDL_Color){255, 255, 255, 255};
	items->size = 24;
	create_text(items, game->window->renderPTR, "Items", "assets/fonts/MontserratBlack.ttf");
	create_button(&game->editor->buttons_entities, select_item, dest, color, hover, items, items, -1);

	dest.y += 100;
	props->color = (SDL_Color){255, 255, 255, 255};
	props->size = 24;
	create_text(props, game->window->renderPTR, "Props", "assets/fonts/MontserratBlack.ttf");
	create_button(&game->editor->buttons_entities, select_props, dest, color, hover, props, props, -1);

	game->editor->entity_text = ". . .";

	return ;
}
