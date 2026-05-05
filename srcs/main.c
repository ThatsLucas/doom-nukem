/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:17:28 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/05 18:07:27 by edurance         ###   ########.fr       */
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

	create_notif(&game->window->PopupPtr.notif_buf, "Le lutin est aux arrivants, envoie le lassot mokhtar, je peux pas je suis au mitar ! QUOOOOOI T fou d'etre au mitard en big 2026!!!!", 5, 35);

	create_notif(&game->window->PopupPtr.notif_buf, "CECI EST UNE GROSSE NOTIF !", 2, 80);

	create_notif(&game->window->PopupPtr.notif_buf, "UN BOSS EST APPARU DANS LA SALLE DES BOSS", 5, 55);

	create_notif(&game->window->PopupPtr.notif_buf, "BANGER CE JEU", 5, 90);

	if (!game->map || !game->map->sectors || game->map->num_sectors == 0)
	{
		printf("ERROR: Map or sectors not initialized!\n");
		return (1);
	}

	t_entity    pnj;

	pnj.type = ENTITY_ENEMY;
	pnj.status = E_STATUS_IDLE;
	pnj.attack_range = 3.0f;

	pnj.vision_angle = 120.0f;
	pnj.vision_range = 15.0f;
	pnj.speed = 2.0f;
	pnj.dir_x = 1.0f;
	pnj.dir_y = 1.0f;
	pnj.num_frames = 8;
	//pnj.textures = malloc(sizeof(SDL_Texture *) * 8);
	//if (!pnj.textures)
	//	return (1);

	//for (int i = 0; i < 8; i++)
	//{
	//	snprintf(path_buf, sizeof(path_buf),
	//		"assets/png/entities/pnj/flamethrow/flamethrow%d.png", i + 1);
	//	pnj_pngs[i].w = 400;
	//	pnj_pngs[i].h = 456;
	//	pnj_pngs[i].path = ft_strdup(path_buf);
	//	printf("Loading: %s\n", pnj_pngs[i].path);
	//	if (!process_png(&pnj_pngs[i]) && !pnj_pngs[i].buf)
	//	{
	//		printf("ERROR: Failed to load %s\n", pnj_pngs[i].path);
	//		return (1);
	//	}
	//	pnj.textures[i] = create_image(&pnj_pngs[i], game->window->renderPTR);
	//	free(pnj_pngs[i].path);
	//}

	pnj.x = game->ply->pos.x + game->ply->dir.x * 2;
	pnj.y = game->ply->pos.y + game->ply->dir.y * 2;
	pnj.z = get_plane_z(game->map->sectors[game->ply->sector].floor_plane, pnj.x, pnj.y);
	pnj.sector = game->ply->sector;
	printf("e->z = %f | ply_z = %f | ply_floor = %f\n", pnj.z, game->ply->z, game->ply->z - EYES_HEIGTH);
	t_png pnj_png;
	pnj_png.w = 300;
	pnj_png.h = 700;
	pnj_png.path = ft_strdup("assets/png/entities/shooter.png");
	printf("%s\n", pnj_png.path);

	if (!process_png(&pnj_png) && !pnj_png.buf)
	{
		printf("ERROR: Failed to load monstre.png\n");
		return (1);
	}

	t_png shoot;
	shoot.w = 300;
	shoot.h = 700;
	shoot.path = ft_strdup("assets/png/entities/shooter_attack.png");
	if (!process_png(&shoot) && !shoot.buf)
	{
		printf("ERROR: Failed to load shoot.png\n");
		return (1);
	}

	pnj.texture = create_image(&pnj_png, game->window->renderPTR);
	pnj.texture_shoot = create_image(&shoot, game->window->renderPTR);

	// Fallback texture unique (frame 0)
	pnj.textures = NULL;
	pnj.num_frames = 0;

	pnj.x = game->ply->pos.x + game->ply->dir.x * 2;
	pnj.y = game->ply->pos.y + game->ply->dir.y * 2;
	pnj.z = get_plane_z(game->map->sectors[game->ply->sector].floor_plane, pnj.x, pnj.y);
	pnj.sector = game->ply->sector;
	pnj.hp = 50;
	pnj.hitbox = 1;
	pnj.can_shoot = 0;
	pnj.last_shot_time = 0;
	pnj.damage = 10;
	pnj.fire_rate = 200;
	add_entity(game, &game->entities, pnj);

	printf("e->z = %f | ply_z = %f | ply_floor = %f\n",
		pnj.z, game->ply->pos.x, game->ply->z - EYES_HEIGTH);

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
		
		// display_notif(game->window, &game->window->PopupPtr.notif_buf);
		
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
