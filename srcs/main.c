/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/10 15:58:55 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI/GUI.h"
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

	const char *weapon_names[] = {"Fists", "Pistol", "Shotgun", "Rocket Launcher"};
	for (int wep = 0; wep < game->ply->inventory.weap_count; wep++)
	{
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
	printf("Weapon held: %s\n", weapon_names[game->ply->held_weap->type]);
	printf("------------------------------\n");

	game->items[0] = (t_ground_item){
		.type = ITEM_CONSUMABLE,
		.data.cons = {CONS_HEAL, 25},
		.pos_x = 600,
		.pos_y = 500,
		.w = 50,
		.h = 50,
		.pickup_range = 50.0f,
		.texture_path = "assets/png/items/cons/medic.bmp"
	};

	game->items[1] = (t_ground_item){
		.type = ITEM_CONSUMABLE,
		.data.cons = {CONS_FUEL, 25},
		.pos_x = 700,
		.pos_y = 500,
		.w = 50,
		.h = 60,
		.pickup_range = 60.0f,
		.texture_path = "assets/png/items/cons/fuel.bmp"
	};

	game->items[2] = (t_ground_item){
		.type = ITEM_CONSUMABLE,
		.data.cons.type = CONS_BATTERY,
		.data.cons.amount = 50,
		.pos_x = 900,
		.pos_y = 500,
		.w = 55,
		.h = 70,
		.pickup_range = 65.0f,
		.texture_path = "assets/png/items/cons/battery.bmp"
	};

	game->items[3] = (t_ground_item){
		.type = ITEM_WEAPON,
		.data.weap = {WEAP_SHOTGUN, 25},
		.pos_x = 500,
		.pos_y = 300,
		.w = 80,
		.h = 40,
		.pickup_range = 60.0f,
		.texture_path = "assets/png/items/weapons/shotgun.bmp"
	};

	game->items[4] = (t_ground_item){
		.type = ITEM_WEAPON,
		.data.weap = {WEAP_PISTOL, 25},
		.pos_x = 700,
		.pos_y = 300,
		.w = 65,
		.h = 50,
		.pickup_range = 55.0f,
		.texture_path = "assets/png/items/weapons/pistol.bmp"
	};

	game->items[5] = (t_ground_item){
		.type = ITEM_WEAPON,
		.data.weap = {WEAP_ROCKET_LAUNCHER, 25},
		.pos_x = 900,
		.pos_y = 300,
		.w = 150,
		.h = 40,
		.pickup_range = 100.0f,
		.texture_path = "assets/png/items/weapons/rocket_launcher.bmp"
	};

	game->items[6] = (t_ground_item){
		.type = ITEM_TOOL,
		.data.tool.type = TOOL_JETPACK,
		.data.tool.data.fuel = 100,
		.pos_x = 750,
		.pos_y = 800,
		.w = 150,
		.h = 150,
		.pickup_range = 150.0f,
		.texture_path = "assets/png/items/tools/jetpack.bmp"
	};

	SDL_Surface *surface_health = SDL_LoadBMP(game->items[0].texture_path);
	SDL_Surface *surface_fuel = SDL_LoadBMP(game->items[1].texture_path);
	SDL_Surface *surface_battery = SDL_LoadBMP(game->items[2].texture_path);
	if (!surface_health || !surface_battery || !surface_fuel)
	{
		printf("Erreur BMP: %s\n", SDL_GetError());
	}
	else
	{
		game->items[0].texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_health);
		SDL_FreeSurface(surface_health);
		if (!game->items[0].texture)
			printf("Erreur Texture: %s\n", SDL_GetError());
		game->items[1].texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_fuel);
		SDL_FreeSurface(surface_fuel);
		if (!game->items[1].texture)
			printf("Erreur Texture: %s\n", SDL_GetError());
		game->items[2].texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_battery);
		SDL_FreeSurface(surface_battery);
		if (!game->items[2].texture)
			printf("Erreur Texture: %s\n", SDL_GetError());
	}

	SDL_Surface *surface_shotgun = SDL_LoadBMP(game->items[3].texture_path);
	SDL_Surface *surface_pistol = SDL_LoadBMP(game->items[4].texture_path);
	SDL_Surface *surface_rocket = SDL_LoadBMP(game->items[5].texture_path);
	SDL_Surface *surface_jetpack = SDL_LoadBMP(game->items[6].texture_path);
	if (!surface_shotgun || !surface_pistol || !surface_rocket || !surface_jetpack)
	{
		printf("Erreur BMP: %s\n", SDL_GetError());
	}
	else
	{
		game->items[3].texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_shotgun);
		SDL_FreeSurface(surface_shotgun);
		if (!game->items[3].texture)
			printf("Erreur Texture: %s\n", SDL_GetError());
		game->items[4].texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_pistol);
		SDL_FreeSurface(surface_pistol);
		if (!game->items[4].texture)
			printf("Erreur Texture: %s\n", SDL_GetError());
		game->items[5].texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_rocket);
		SDL_FreeSurface(surface_rocket);
		if (!game->items[5].texture)
			printf("Erreur Texture: %s\n", SDL_GetError());
		game->items[6].texture = SDL_CreateTextureFromSurface(game->window->renderPTR, surface_jetpack);
		SDL_FreeSurface(surface_jetpack);
		if (!game->items[6].texture)
			printf("Erreur Texture: %s\n", SDL_GetError());
	}

	game->items_count += 7;

	while (1)
	{
		events_handler(game);
		update_item(game);

		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 78, 78, 78, 255);
		SDL_RenderClear(game->window->renderPTR);

		display_buttons(game->window->buttonList, game->window->renderPTR);
		// Creation du renderer (de la frame)
		// SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);
		draw_player(game->window->renderPTR, game->ply, 20, rgb);

		render_items(game);
		pickup_flash(game);

		display_hud(game);

		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
	}

	exit_game(game, NULL);

	return 0;
}
