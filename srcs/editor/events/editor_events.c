/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:50:59 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/08/11 14:17:35 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

static void	check_toggles(t_game *game, int x, int y)
{
	SDL_Rect	box;

	box.h = 35; box.w = 80; box.x = 1639; box.y = 495;
	to_responsive(game->window, &box);

	if (x > box.x && x < box.x + box.w && y > box.y && y < box.y + box.h)
		game->editor->properties.slope_fc = game->editor->properties.slope_fc == 0 ? 1 : 0;	//slopes

	box.h = 35; box.w = 80; box.x = 1730; box.y = 911;
	to_responsive(game->window, &box);

	if (x > box.x && x < box.x + box.w && y > box.y && y < box.y + box.h)
		game->editor->properties.wall_collisions = game->editor->properties.wall_collisions == 0 ? 1 : 0;	//collisions wall

	return ;
}

static void	mouse_button_down(t_game *game, SDL_Event *e)
{
	get_selected_input(game, &game->editor->text_inputs, e->motion.x, e->motion.y);
	check_button_pressed(game, game->editor->buttons);
	if (game->editor->selected_tool == 3)
		entities_events(game, e);
	if (!get_clicked_editor_button(game, e->motion.x, e->motion.y))
		plan_click(game, e);
	get_clicked_texture(game, e->motion.x, e->motion.y);
	get_clicked_texture_button(game, e->motion.x, e->motion.y);
	check_toggles(game, e->motion.x, e->motion.y);
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
				editor_text_input(game->editor, e.text.text);
				break ;

			case SDL_KEYDOWN:
				editor_key_down(game->editor, e.key.keysym.sym, game);
				break ;

			case SDL_MOUSEBUTTONDOWN:
				mouse_button_down(game, &e);
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
