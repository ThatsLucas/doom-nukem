/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:35:44 by edurance          #+#    #+#             */
/*   Updated: 2026/08/09 15:54:38 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

int	default_enemy(t_game *game, t_vect2 pos, char *idle_tex, char *shoot_tex, int w, int h)
{
	t_entity	e;

	e.type = ENTITY_ENEMY;
	e.status = E_STATUS_IDLE;
	e.attack_range = 3.0f;
	e.vision_angle = 360.0f;
	e.vision_range = 10.0f;
	e.speed = 2.0f;
	e.dir_x = 1.0f;
	e.dir_y = 1.0f;
	e.num_frames = 0;
	e.textures = 0;
	e.x = pos.x;
	e.y = pos.y;
	e.hp = 100;
	e.hitbox = 1;
	e.last_shot_time = 0;
	e.damage = 15;
	e.fire_rate = 200;

	e.sector = find_sector(game->map, pos);
	if (e.sector == -1)
		return (0);
	e.z = get_plane_z(game->map->sectors[e.sector].floor_plane, pos.x, pos.y);

	t_png	idle, shoot;
	idle.w = w; shoot.w = w;
	idle.h = h; shoot.h = h;
	idle.path = ft_strdup(idle_tex); shoot.path = ft_strdup(shoot_tex);
	if (!process_png(&idle))
		exit_game(game, "Failed to load enemy");
	if (!process_png(&shoot))
		exit_game(game, "Failed to load enemy (shoot text)");

	if (!(e.texture = create_image(&idle, game->window->renderPTR))
		|| !(e.texture_shoot = create_image(&shoot, game->window->renderPTR)))
		exit_game(game, "Failed to create image enemy");
	e.sprite_w = (float)w;
	e.sprite_h = (float)h;

	add_entity(game, &game->entities, e);
	return (1);
}

void	default_pnj(t_game *game, t_vect2 pos, char *paths[], int size, int w, int h, float dir_x, float dir_y, char *notif)
{
	t_entity	e;
	t_png		png;

	e.type = ENTITY_PNJ;
	e.status = E_STATUS_IDLE;
	
	e.sector = find_sector(game->map, pos);
	e.dir_x = dir_x;
	e.dir_y = dir_y;
	e.z = get_plane_z(game->map->sectors[e.sector].floor_plane, pos.x, pos.y);
	e.x = pos.x; e.y = pos.y;
	e.hp = 1000;
	e.notif = notif;

	e.num_frames = size;
	e.textures = malloc(sizeof(SDL_Texture *) * size);
	if (!e.textures)
		exit_game(game, "Failed to malloc default pnj");

	for (int i = 0; i < size; i++)
	{
		png.w = w;
		png.h = h;
		png.path = ft_strdup(paths[i]);
		if (!png.path)
			exit_game(game, "Failed to strdup default pnj");
		if (!process_png(&png))
			exit_game(game, "Failed to process default pnj");
		e.textures[i] = create_image(&png, game->window->renderPTR);
		if (!e.textures[i])
			exit_game(game, "Failed to create image default pnj");
	}

	e.texture = e.textures[0];
	e.hitbox = 1;
	e.sprite_w = (float)w;
	e.sprite_h = (float)h;
	add_entity(game, &game->entities, e);
}

void	create_pnj1(t_game *game, t_vect2 pos, t_vect2 dir)
{
	t_entity	e;
	t_png		png;

	e.type = ENTITY_PNJ;
	e.status = E_STATUS_IDLE;

	/*a changer pour trouver le bon secteur*/
	e.sector = find_sector(game->map, pos);
	e.dir_x = dir.x;
	e.dir_y = dir.y;
	e.z = get_plane_z(game->map->sectors[e.sector].floor_plane, pos.x, pos.y);
	e.x = pos.x; e.y = pos.y;
	e.hp = 1000;
	e.notif = "Aide nous !"; // a modif en fonction de l'histoire

	e.num_frames = 8;
	e.textures = malloc(sizeof(SDL_Texture *) * 8);
	if (!e.textures)
		exit_game(game, "Failed to malloc pnj1");

	for (int i = 1; i < 9; i++)
	{
		png.w = 400;
		png.h = 600;
		char path[200];
		sprintf(path, "assets/png/entities/pnj/tung/tung%d.png", i);
		png.path = ft_strdup(path);
		if (!png.path)
			exit_game(game, "Failed to strdup default pnj");
		if (!process_png(&png))
			exit_game(game, "Failed to process default pnj");
		e.textures[i] = create_image(&png, game->window->renderPTR);
		if (!e.textures[i])
			exit_game(game, "Failed to create image default pnj");
	}

	e.texture = e.textures[0];
	e.hitbox = 1;
	e.sprite_w = 400.0f;
	e.sprite_h = 600.0f;
	add_entity(game, &game->entities, e);
}

void	create_enemy1(t_game *game, t_vect2 pos)
{
	t_entity	e;
	t_png	idle, shoot, dead;
	char	*idle_tex = "assets/png/entities/enemies/enemy1/idle.png";
	char	*shoot_tex = "assets/png/entities/enemies/enemy1/shoot.png";
	char	*dead_tex = "assets/png/entities/enemies/enemy1/dead.png";

	e.type = ENTITY_ENEMY;
	e.status = E_STATUS_IDLE;
	e.attack_range = 3.0f;
	e.vision_angle = 360.0f;
	e.vision_range = 10.0f;
	e.speed = 2.0f;
	e.dir_x = 1.0f;
	e.dir_y = 1.0f;
	e.num_frames = 0;
	e.textures = 0;
	e.x = pos.x;
	e.y = pos.y;
	e.hp = 100;
	e.hitbox = 1;
	e.last_shot_time = 0;
	e.damage = 15;
	e.fire_rate = 200;

	/* pour voir z -> a changer */
	e.sector = find_sector(game->map, pos);
	if (e.sector == -1)
		exit_game(game, "Failed to find sector");
	e.z = get_plane_z(game->map->sectors[e.sector].floor_plane, pos.x, pos.y);

	idle.w = 400; idle.h = 600;
	shoot.w = 400; shoot.h = 600;
	dead.w = 200; dead.h = 50; 
	idle.path = ft_strdup(idle_tex); shoot.path = ft_strdup(shoot_tex); dead.path = ft_strdup(dead_tex);
	if (!process_png(&idle))
		exit_game(game, "Failed to load enemy1 (idle tex)");
	if (!process_png(&shoot))
		exit_game(game, "Failed to load enemy1 (shoot text)");
	if (!process_png(&dead))
		exit_game(game, "Failed to load enemy1 (dead tex)");

	if (!(e.texture = create_image(&idle, game->window->renderPTR))
		|| !(e.texture_shoot = create_image(&shoot, game->window->renderPTR)) || !(e.texture_dead = create_image(&dead, game->window->renderPTR)))
		exit_game(game, "Failed to create image enemy1");

	add_entity(game, &game->entities, e);
}

void	create_enemy2(t_game *game, t_vect2 pos)
{
	t_entity	e;
	t_png	idle, shoot, dead;
	char	*idle_tex = "assets/png/entities/enemies/enemy2/idle.png";
	char	*shoot_tex = "assets/png/entities/enemies/enemy2/shoot.png";
	char	*dead_tex = "assets/png/entities/enemies/enemy2/dead.png";

	e.type = ENTITY_ENEMY;
	e.status = E_STATUS_IDLE;
	e.attack_range = 4.0f;
	e.vision_angle = 360.0f;
	e.vision_range = 10.0f;
	e.speed = 1.0f;
	e.dir_x = 1.0f;
	e.dir_y = 1.0f;
	e.num_frames = 0;
	e.textures = 0;
	e.x = pos.x;
	e.y = pos.y;
	e.hp = 130;
	e.hitbox = 1;
	e.last_shot_time = 0;
	e.damage = 5;
	e.fire_rate = 70;

	/* pour voir z -> a changer */
	e.sector = find_sector(game->map, pos);
	if (e.sector == -1)
		exit_game(game, "Failed to find sector");
	e.z = get_plane_z(game->map->sectors[e.sector].floor_plane, pos.x, pos.y);

	idle.w = 690; idle.h = 680;
	shoot.w = 690; shoot.h = 680;
	dead.w = 700; dead.h = 300;
	idle.path = ft_strdup(idle_tex); shoot.path = ft_strdup(shoot_tex); dead.path = ft_strdup(dead_tex);
	if (!process_png(&idle))
		exit_game(game, "Failed to load enemy2 (idle tex)");
	if (!process_png(&shoot))
		exit_game(game, "Failed to load enemy2 (shoot text)");
	if (!process_png(&dead))
		exit_game(game, "Failed to load enemy2 (dead text)");

	if (!(e.texture = create_image(&idle, game->window->renderPTR))
		|| !(e.texture_shoot = create_image(&shoot, game->window->renderPTR)) || !(e.texture_dead = create_image(&dead, game->window->renderPTR)))
		exit_game(game, "Failed to create image enemy2");
	e.sprite_w = 690.0f;
	e.sprite_h = 680.0f;

	add_entity(game, &game->entities, e);
}

void	create_enemy3(t_game *game, t_vect2 pos)
{
	t_entity	e;
	t_png	idle, shoot, dead;
	char	*idle_tex = "assets/png/entities/enemies/enemy3/idle.png";
	char	*shoot_tex = "assets/png/entities/enemies/enemy3/shoot.png";
	char	*dead_tex = "assets/png/entities/enemies/enemy3/dead.png";

	e.type = ENTITY_ENEMY;
	e.status = E_STATUS_IDLE;
	e.attack_range = 4.0f;
	e.vision_angle = 360.0f;
	e.vision_range = 10.0f;
	e.speed = 1.5f;
	e.dir_x = 1.0f;
	e.dir_y = 1.0f;
	e.num_frames = 0;
	e.textures = 0;
	e.x = pos.x;
	e.y = pos.y;
	e.hp = 250;
	e.hitbox = 1;
	e.last_shot_time = 0;
	e.damage = 10;
	e.fire_rate = 200;

	/* pour voir z -> a changer */
	e.sector = find_sector(game->map, pos);
	if (e.sector == -1)
		exit_game(game, "Failed to find sector");
	e.z = get_plane_z(game->map->sectors[e.sector].floor_plane, pos.x, pos.y);

	idle.w = 400; idle.h = 600;
	shoot.w = 400; shoot.h = 600;
	dead.w = 500; dead.h = 200;
	idle.path = ft_strdup(idle_tex); shoot.path = ft_strdup(shoot_tex); dead.path = ft_strdup(dead_tex);
	if (!process_png(&idle))
		exit_game(game, "Failed to load enemy3 (idle tex)");
	if (!process_png(&shoot))
		exit_game(game, "Failed to load enemy3 (shoot text)");
	if (!process_png(&dead))
		exit_game(game, "Failed to load enemy3 (dead text)");

	if (!(e.texture = create_image(&idle, game->window->renderPTR))
		|| !(e.texture_shoot = create_image(&shoot, game->window->renderPTR)) || !(e.texture_dead = create_image(&dead, game->window->renderPTR)))
		exit_game(game, "Failed to create image enemy3");
	e.sprite_w = 400.0f;
	e.sprite_h = 600.0f;

	add_entity(game, &game->entities, e);
}

void	create_boss1(t_game *game, t_vect2 pos)
{
	t_entity	e;
	t_png	idle, shoot, dead;

	char	*idle_tex = "assets/png/entities/boss/boss1/idle.png";
	char	*shoot_tex = "assets/png/entities/boss/boss1/shoot.png";
	char	*dead_tex = "assets/png/entities/boss/boss1/dead.png";

	e.type = ENTITY_BOSS;
	e.status = E_STATUS_IDLE;
	e.attack_range = 5.0f;
	e.vision_angle = 360.0f;
	e.vision_range = 10.0f;
	e.speed = 3.0f;
	e.dir_x = 1.0f;
	e.dir_y = 1.0f;
	e.num_frames = 0;
	e.textures = 0;
	e.x = pos.x;
	e.y = pos.y;
	e.hp = 500;
	e.hitbox = 1;
	e.last_shot_time = 0;
	e.damage = 20;
	e.fire_rate = 130;

	/* pour voir z -> a changer */
	e.sector = find_sector(game->map, pos);
	if (e.sector == -1)
		exit_game(game, "Failed to find sector");
	e.z = get_plane_z(game->map->sectors[e.sector].floor_plane, pos.x, pos.y);

	int boss_w = 1500;
	int boss_h = 700;
	idle.w = boss_w; idle.h = boss_h;
	shoot.w = boss_w; shoot.h = boss_h;
	dead.w = 1300; dead.h = 400;
	idle.path = ft_strdup(idle_tex); shoot.path = ft_strdup(shoot_tex); dead.path = ft_strdup(dead_tex);
	if (!process_png(&idle))
		exit_game(game, "Failed to load boss1 (idle tex)");
	if (!process_png(&shoot))
		exit_game(game, "Failed to load boss1 (shoot text)");
	if (!process_png(&dead))
		exit_game(game, "Failed to load boss1 (dead tex)");

	if (!(e.texture = create_image(&idle, game->window->renderPTR))
		|| !(e.texture_shoot = create_image(&shoot, game->window->renderPTR)) || !(e.texture_dead = create_image(&dead, game->window->renderPTR)))
		exit_game(game, "Failed to create image boss1");
	e.sprite_w = (float)boss_w;
	e.sprite_h = (float)boss_h;

	add_entity(game, &game->entities, e);
}
