/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/08 12:31:28 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI.h"
#include "Game.h"
#include "Events.h"
#include "parser/PNG.h"

int main(void)
{

	process_png("assets/png/doom_nukem.png");

	t_game	*game;

	game = init_game();
	if (!game)
		return (1);

	t_RGB rgb;
	rgb.r = 51;
	rgb.g = 153;
	rgb.b = 255;
	rgb.alphaValue = 255;

	t_coordinates coords;
	coords.x = 200;
	coords.y = 200;
	coords.w = 150;
	coords.h = 80;

	t_RGB buttoncolor;
	buttoncolor.r = 0;
	buttoncolor.g = 60;
	buttoncolor.b = 200;
	buttoncolor.alphaValue = 255;

	t_RGB hoverColor;
	hoverColor.r = 90;
	hoverColor.g = 60;
	hoverColor.b = 150;
	hoverColor.alphaValue = 255;

	create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);
	coords.x = 200;
	coords.y = 300;
	create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);
	coords.x = 200;
	coords.y = 400;
	create_button(&game->window->buttonList, NULL, coords, buttoncolor, hoverColor);

	printf("------------------------------\n");	
	printf("items:\n");

	for (int wep = 0; wep < game->ply->inventory.weap_count; wep++)
	{
		const char *weapon_names[] = {"Pistol", "Shotgun", "Rocket Launcher"};
		t_weapon *w = &game->ply->inventory.weapons[wep];
		printf("weapon[%d]: type=%s ammo=%d\n", wep, weapon_names[w->type], w->ammo);
	}

	for (int tool = 0; tool < game->ply->inventory.tool_count; tool++)
	{
		const char *tool_names[] = {"Flashlight", "Key", "Jetpack"};
		t_tool *t = &game->ply->inventory.tools[tool];
		printf("tool[%d]: type=%s ", tool, tool_names[t->type]);

		if (t->type == TOOL_FLASHLIGHT)
			printf("battery=%d\n", t->data.battery);
		else if (t->type == TOOL_KEY)
			printf("id=%d\n", t->data.id);
		else if (t->type == TOOL_JETPACK)
			printf("fuel=%d\n", t->data.fuel);
	}

	printf("\n");

	printf("Health: %d\n", game->ply->hp);
	printf("------------------------------\n");

	while (1)
	{
		events_handler(game);

		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 150, 0, 0, 255);
		SDL_RenderClear(game->window->renderPTR);

		display_buttons(game->window->buttonList, game->window->renderPTR);
		// Creation du renderer (de la frame)
		// SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);
		draw_player(game->window->renderPTR, game->ply, 20, rgb);

		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
	}

	exit_game(game, NULL);

	return 0;
}
