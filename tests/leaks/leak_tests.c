/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 15:00:00 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/29 15:00:00 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Scénarios de test pour détecter les fuites mémoire.
	Chaque scénario lance le vrai jeu, simule une partie (niveaux, game over,
	écran de fin, notifs...) puis quitte avec exit_game : LeakSanitizer
	vérifie alors que tout a été libéré. Lancer avec : make leaks
*/

#include "Game.h"
#include "Events.h"
#include "menus/menus.h"
#include "multiplayer/server.h"
#include "Editor.h"

/* Une image du jeu, comme game_frame dans main.c (sans lire le clavier/souris). */
static void	frame(t_game *game)
{
	SDL_PumpEvents();
	SDL_RenderClear(game->window->renderPTR);
	draw_current_menu(game);
	display_notif(game->window, &game->window->menus.notif.notif_buf);
	display_fps(game);
	SDL_RenderPresent(game->window->renderPTR);
}

/* Fait tourner le jeu pendant ms millisecondes. */
static void	run_for(t_game *game, Uint64 ms)
{
	Uint64	end = SDL_GetTicks64() + ms;

	while (SDL_GetTicks64() < end)
		frame(game);
}

/* Lance le jeu comme main.c. */
static t_game	*start_game(void)
{
	t_game	*game;

	game = init_game();
	if (!game)
		exit(2);
	ft_bzero(&game->ply->keys, sizeof(t_keys));
	free_map(game->map);
	game->map = load_map("level1", game, 0);
	if (!game->map)
		exit_game(game, "leak_tests: failed to load level1");
	game->current_level = 1;
	game->window->menus.current = 1;
	pthread_mutex_init(&game->serverStatus.lock, NULL);
	pthread_create(&game->serverThread, NULL, create_server, game);
	return (game);
}

/* Vérifie une condition du scénario, quitte avec le code 3 si elle est fausse. */
static void	check(t_game *game, int ok, char *what)
{
	if (ok)
		return ;
	ft_dprintf(STDERR_FILENO, "leak_tests: CHECK FAILED: %s\n", what);
	exit(3);
	(void)game;
}

/* Lance le jeu, affiche le menu, quitte. */
static void	test_startup(t_game *game)
{
	run_for(game, 1000);
}

/* Charge les 3 niveaux à la suite (rechargement de carte, entités, objets). */
static void	test_levels(t_game *game)
{
	for (int level = 1; level <= 3; level++)
	{
		load_level(game, level);
		game->window->menus.current = 0;
		run_for(game, 800);
	}
	load_level(game, 1);
	game->window->menus.current = 0;
	run_for(game, 800);
}

/* Le joueur meurt, l'écran de game over renvoie au menu, puis on relance. */
static void	test_game_over(t_game *game)
{
	load_level(game, 1);
	game->window->menus.current = 0;
	run_for(game, 500);
	game->ply->hp = 0;
	run_for(game, (GAME_OVER_DURATION + 1) * 1000);
	check(game, game->window->menus.current == 1, "game over did not return to menu");
	load_level(game, 1);
	check(game, game->ply->hp > 0, "player not reset after game over");
	game->window->menus.current = 0;
	run_for(game, 500);
}

/* Le boss du niveau 3 meurt, l'écran de fin renvoie au menu. */
static void	test_victory(t_game *game)
{
	load_level(game, 3);
	game->window->menus.current = 0;
	run_for(game, 500);
	for (int i = 0; i < game->entities.count; i++)
	{
		if (game->entities.list[i].type == ENTITY_BOSS)
		{
			game->entities.list[i].hp = 0;
			game->entities.list[i].status = E_STATUS_DEAD;
		}
	}
	run_for(game, (VICTORY_DURATION + 1) * 1000);
	check(game, game->window->menus.current == 1, "victory did not return to menu");
}

/* Des notifs qui s'affichent jusqu'au bout, et d'autres encore en attente à la sortie. */
static void	test_notifs(t_game *game)
{
	t_notif_buf	**buf = &game->window->menus.notif.notif_buf;
	Uint64		timeout = SDL_GetTicks64() + 30000;

	for (int i = 0; i < 3; i++)
		create_notif(buf, "Leak test notification", 1, 40);
	while (*buf && SDL_GetTicks64() < timeout)
		frame(game);
	check(game, *buf == NULL, "notifications never left the queue");
	create_notif(buf, "Pending notification 1", 5, 40);
	create_notif(buf, "Pending notification 2", 5, 40);
	run_for(game, 300);
}

/* Change de langue 4 fois, comme dans les paramètres. */
static void	test_languages(t_game *game)
{
	for (int i = 0; i < 4; i++)
	{
		game->selected_language = i;
		free_languages(game);
		parse_languages(game, i);
		refresh_main_menu_texts(game);
		refresh_settings_texts(game, &game->window->menus.settings);
		refresh_lobby_texts(game);
		refresh_cinematics_texts(game);
		refresh_pause_menu_texts(game);
		refresh_game_over_texts(game);
		refresh_victory_texts(game);
		run_for(game, 200);
	}
}

/* Tire des roquettes (projectiles, explosions) et joue les sons d'arme. */
static void	test_combat(t_game *game)
{
	load_level(game, 1);
	game->window->menus.current = 0;
	for (int i = 0; i < 3; i++)
	{
		spawn_rocket(game);
		play_sound(game->sounds.rocket);
		play_sound(game->sounds.shot);
		run_for(game, 300);
	}
	run_for(game, 2000);
}

/* Joue les 3 cinématiques. */
static void	test_cinematics(t_game *game)
{
	t_cinematic	*cinematic = &game->window->menus.cinematic;

	for (int menu = 5; menu <= 7; menu++)
	{
		cinematic->cinematatic_duration = CINEMATIC_ONE_DURATION;
		cinematic->cinematatic_begin_time = 0;
		game->window->menus.current = menu;
		run_for(game, 700);
	}
}

/* Une image de l'éditeur, comme editor_frame dans main.c (sans lire le clavier/souris). */
static void	editor_frame_for(t_game *game, Uint64 ms)
{
	Uint64	end = SDL_GetTicks64() + ms;

	while (SDL_GetTicks64() < end)
	{
		SDL_PumpEvents();
		SDL_RenderClear(game->window->renderPTR);
		display_editor(game);
		SDL_RenderPresent(game->window->renderPTR);
	}
}

/* Remplace la carte de l'éditeur, comme le bouton "load". */
static void	editor_load(t_game *game, char *name)
{
	t_map	*map;

	map = load_map(name, game, 1);
	check(game, map != NULL, "editor could not load map");
	free_map(game->editor->map);
	game->editor->map = map;
	fit_grid_view(game);
}

/* Dessine une pièce carrée dans l'éditeur. */
static void	editor_draw_room(t_game *game)
{
	int	v[4];

	clear_editor_plan(game);
	v[0] = editor_add_vertice(game, 1.0f, 1.0f);
	v[1] = editor_add_vertice(game, 5.0f, 1.0f);
	v[2] = editor_add_vertice(game, 5.0f, 5.0f);
	v[3] = editor_add_vertice(game, 1.0f, 5.0f);
	for (int i = 0; i < 4; i++)
		editor_add_wall(game, v[i], v[(i + 1) % 4]);
	compute_sectors(game->editor->map);
	precompute_lengths(game->editor->map);
	precompute_next_sectors(game->editor->map);
}

/* Utilise les principales actions de l'éditeur. */
static void	test_editor(t_game *game)
{
	t_editor	*editor = game->editor;
	t_vect2		wall_mid = {3.0f, 1.0f};
	SDL_Texture	*selected = NULL;
	int			selected_index = 0;

	game->window->menus.current = -1;
	editor_frame_for(game, 500);
	editor_load(game, "level1");
	editor_frame_for(game, 500);
	editor_load(game, "level3");
	editor_frame_for(game, 500);
	editor_draw_room(game);
	editor_frame_for(game, 300);
	check(game, editor->map->num_sectors > 0, "editor room has no sector");
	check(game, add_decal(game, editor->map, "assets/png/items/decals/switch.png", 0.5f, wall_mid) == 0, "add_decal failed");
	check(game, add_decal(game, editor->map, "assets/png/items/decals/window_tree.png", 2.0f, wall_mid) == 0, "add_decal failed");
	check(game, suppress_decal(game, wall_mid) == 1, "suppress_decal failed");
	create_texture_selector(game, &selected, &selected_index);
	editor_frame_for(game, 300);
	editor->texture_selector.display = 0;
	check(game, save_map("leak_test_map", editor->map) == 0, "save_map failed");
	editor_load(game, "leak_test_map");
	unlink("saves/leak_test_map");
	editor_frame_for(game, 300);
	editor_draw_room(game);
	suppress_wall(game, 0);
	compute_sectors(editor->map);
	suppress_vertice(game, 5.0f, 5.0f);
	compute_sectors(editor->map);
	editor_frame_for(game, 300);
	editor_draw_room(game);
	game->window->menus.current = 1;
	run_for(game, 300);
}

/* Une image du jeu qui lit les événements, comme game_frame dans main.c. */
static void	play_for(t_game *game, Uint64 ms)
{
	Uint64	end = SDL_GetTicks64() + ms;

	do
	{
		if (game->ply->hp > 0)
			game->ply->hp = 100; // les ennemis ne doivent pas tuer le joueur pendant le test
		SDL_RenderClear(game->window->renderPTR);
		events_handler(game);
		draw_current_menu(game);
		display_notif(game->window, &game->window->menus.notif.notif_buf);
		display_fps(game);
		SDL_RenderPresent(game->window->renderPTR);
	} while (SDL_GetTicks64() < end);
}

/* Envoie un appui ou un relâchement de touche, comme le clavier. */
static void	push_key(SDL_Keycode key, int down)
{
	SDL_Event	e;

	ft_bzero(&e, sizeof(e));
	e.type = down ? SDL_KEYDOWN : SDL_KEYUP;
	e.key.state = down ? SDL_PRESSED : SDL_RELEASED;
	e.key.keysym.sym = key;
	SDL_PushEvent(&e);
}

/* Maintient une touche enfoncée pendant ms millisecondes. */
static void	hold_key(t_game *game, SDL_Keycode key, Uint64 ms)
{
	push_key(key, 1);
	play_for(game, ms);
	push_key(key, 0);
	play_for(game, 50);
}

/* Envoie un clic, un mouvement ou une molette de souris. */
static void	push_mouse(Uint32 type, int a, int b)
{
	SDL_Event	e;

	ft_bzero(&e, sizeof(e));
	e.type = type;
	if (type == SDL_MOUSEBUTTONDOWN || type == SDL_MOUSEBUTTONUP)
	{
		e.button.button = SDL_BUTTON_LEFT;
		e.button.state = (type == SDL_MOUSEBUTTONDOWN) ? SDL_PRESSED : SDL_RELEASED;
	}
	else if (type == SDL_MOUSEMOTION)
	{
		e.motion.xrel = a;
		e.motion.yrel = b;
	}
	else if (type == SDL_MOUSEWHEEL)
		e.wheel.y = a;
	SDL_PushEvent(&e);
}

/* Ramasse tous les objets du niveau en téléportant le joueur dessus. */
static void	pick_up_all_items(t_game *game)
{
	for (int i = 0; i < game->items_count; i++)
	{
		if (game->items[i].picked_up)
			continue ;
		game->ply->pos = (t_vect2){game->items[i].pos_x, game->items[i].pos_y};
		game->ply->sector = find_sector(game->map, game->ply->pos);
		play_for(game, 100);
	}
}

/* Joue comme un joueur : clavier, souris, tirs, objets, pause, changement de niveau. */
static void	test_gameplay(t_game *game)
{
	t_settings	*set = &game->settings;

	for (int level = 1; level <= 3; level++)
	{
		load_level(game, level);
		game->window->menus.current = 0;
		play_for(game, 300);
		hold_key(game, set->move_forward, 400);
		hold_key(game, set->move_left, 200);
		hold_key(game, set->move_backward, 200);
		hold_key(game, set->move_right, 200);
		push_key(SDLK_LSHIFT, 1);
		hold_key(game, set->move_forward, 300);
		push_key(SDLK_LSHIFT, 0);
		push_key(SDLK_LCTRL, 1);
		hold_key(game, set->move_forward, 300);
		push_key(SDLK_LCTRL, 0);
		hold_key(game, SDLK_SPACE, 200);
		hold_key(game, 1073741904, 200);	// flèche gauche
		hold_key(game, 1073741903, 200);	// flèche droite
		hold_key(game, 1073741906, 100);	// flèche haut
		hold_key(game, 1073741905, 100);	// flèche bas
		push_mouse(SDL_MOUSEMOTION, 40, 10);
		mouse_moves(40, 10, game);
		play_for(game, 100);
		pick_up_all_items(game);
		for (int i = 0; i < 4; i++)
		{
			push_mouse(SDL_MOUSEWHEEL, 1, 0);
			push_mouse(SDL_MOUSEBUTTONDOWN, 0, 0);
			push_mouse(SDL_MOUSEBUTTONUP, 0, 0);
			play_for(game, 400);
		}
		hold_key(game, SDLK_f, 100);
		hold_key(game, SDLK_e, 100);
		hold_key(game, SDLK_p, 100);
		play_for(game, 200);
		hold_key(game, SDLK_p, 100);
		hold_key(game, SDLK_f, 100);
		play_for(game, 500);
		int picked = 0;
		for (int i = 0; i < game->items_count; i++)
			picked += game->items[i].picked_up;
		ft_printf("gameplay: level %d, items %d/%d, weapons %d, pos %d,%d\n", level,
			picked, game->items_count, game->ply->inventory.weap_count,
			(int)game->ply->pos.x, (int)game->ply->pos.y);
	}
}

typedef struct s_leak_test
{
	char	*name;
	void	(*run)(t_game *game);
}			t_leak_test;

int	main(int argc, char **argv)
{
	static t_leak_test	tests[] = {
		{"startup", test_startup},
		{"levels", test_levels},
		{"game_over", test_game_over},
		{"victory", test_victory},
		{"notifs", test_notifs},
		{"languages", test_languages},
		{"combat", test_combat},
		{"cinematics", test_cinematics},
		{"editor", test_editor},
		{"gameplay", test_gameplay},
	};
	int					count = sizeof(tests) / sizeof(tests[0]);
	t_game				*game;

	if (argc != 2)
	{
		for (int i = 0; i < count; i++)
			ft_printf("%s\n", tests[i].name);
		return (0);
	}
	for (int i = 0; i < count; i++)
	{
		if (ft_strcmp(argv[1], tests[i].name) == 0)
		{
			game = start_game();
			tests[i].run(game);
			exit_game(game, NULL);
		}
	}
	ft_dprintf(STDERR_FILENO, "leak_tests: unknown test '%s'\n", argv[1]);
	return (1);
}
