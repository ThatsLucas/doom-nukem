/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/06/08 11:55:30 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "GUI/GUI.h"
#include "menus/menus.h"
#include "Game.h"
#include "Events.h"
#include "parser/PNG.h"

int main(void)
{
	t_game	*game;

	game = init_game();
	if (!game)
		return (1);

	game->ply->pos.x = 3.0f;
	game->ply->pos.y = 2.0f;
	game->ply->dir.x = 0.0f;
	game->ply->dir.y = 1.0f;
	game->ply->sector = 0;
	ft_bzero(&game->ply->keys, sizeof(t_keys));

	game->mapSize[0] = 50;	game->mapSize[1] = 50;

	if (!game->map || !game->map->sectors || game->map->num_sectors == 0)
	{
		printf("ERROR: Map or sectors not initialized!\n");
		return (1);
	}

	char		**path_buf;
	char		buf[64];
	path_buf = malloc(sizeof(char *) * 10);

	for (int i = 0; i < 8; i++)
	{
		snprintf(buf, sizeof(buf), "assets/png/entities/pnj/flamethrow/flamethrow%d.png", i + 1);
		path_buf[i] = ft_strdup(buf);
	}
	t_vect2	pos;
	pos.x = game->ply->pos.x + 5;
	pos.y = game->ply->pos.y + 5;
	default_pnj(game, pos, path_buf, 8, 400, 450, game->ply->dir.x, game->ply->dir.y, "salut a toi je suis heureux de te voir mon gars");


	t_ground_item item;

	// Position
	item.pos_x = game->ply->pos.x + 5;
	item.pos_y = game->ply->pos.y + 5;
	item.pos_z = 0.0f;
	item.pickup_range = 0.8f;
	item.picked_up = 0;

	// Type et données
	item.type = ITEM_WEAPON;
	item.data.weap.type = WEAP_SHOTGUN;
	item.data.weap.ammo = 25;

	// Texture
	item.texture_path = ft_strdup("assets/png/entities/shotgun.png");
	t_png texture;
	texture.path = item.texture_path;
	process_png(&texture);
	if (!texture.buf)
	{
	printf("ERROR: Failed to load shotgun.png\n");
	return (1);
	}
	item.texture = create_image(&texture, game->window->renderPTR);
	item.w = 500;
	item.h = 150;
	item.world_height = 0.6;
	item.aspect_ratio = 500.0f / 150.0f;

	 // Ajout dans le tableau
	 add_item(game, item);

	for (int i = 0; i < game->entities.count; i++)
	{
		printf("ENTITY %d -> x:%f y:%f type:%d\n",
			i,
			game->entities.list[i].x,
			game->entities.list[i].y,
			game->entities.list[i].type);
	}

	while (1)
	{
		events_handler(game);
		update_item(game);
		
		// Clear la page (fond rouge)
		SDL_SetRenderDrawColor(game->window->renderPTR, 51, 20, 7, 255);
		SDL_RenderClear(game->window->renderPTR);
		
		// draw_main_menu(&game->window->MainMenu, game);
		send_rays(game);
		SDL_UpdateTexture(game->frame, NULL, game->frame_buffer, game->screenSize[0] * sizeof(Uint32));
		SDL_RenderCopy(game->window->renderPTR, game->frame, NULL, NULL);
		
		render_entities(game);
		render_items(game);
		
		display_notif(game->window, &game->window->PopupPtr.notif_buf);
		
		// display_buttons(game->window->buttonList, game->window->renderPTR);		
		// Creation du renderer (de la frame)
		// SDL_RenderFillCircle(game->window->renderPTR, game->ply->pos_x, game->ply->pos_y, 20, rgb);
		// draw_player(game->window->renderPTR, game->ply, 20, rgb);
		
		display_hud(game);
		display_fps(game);

		pickup_flash(game);
		// affichage du renderer sur la page
		SDL_RenderPresent(game->window->renderPTR);
	}

	exit_game(game, NULL);
	return 0;
}
