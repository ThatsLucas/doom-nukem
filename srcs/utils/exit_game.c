/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:57:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/28 22:43:05 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "menus/menus.h"

/* Affiche le message d’erreur avant la fermeture du jeu. */
static void print_exit_error(char *type)
{
	const char *error = SDL_GetError();

	if (type && error && error[0])
	{
		ft_dprintf(STDERR_FILENO, "%s => %s\n", type, error);
	}
	else if (type)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", type);
	}
}

/* Libère les ressources de la fenêtre. */
static void free_window(t_WIN *win)
{
	if (!win)
		return ;
	while (win->menus.notif.notif_buf)
		destroy_notif_node(&win->menus.notif.notif_buf);
	if (win->buttonList)
		free_buttons(win->buttonList);
	if (win->renderPTR)
		SDL_DestroyRenderer(win->renderPTR);
	if (win->winPTR)
		SDL_DestroyWindow(win->winPTR);
	free(win);
}

/* Libère toutes les ressources et quitte le jeu. */
void exit_game(t_game *game, char *type)
{
	print_exit_error(type);

	if (!game)
		exit(1);

	cleanup_items(game);
	free_projectiles(game);
	free_hud_cache(game);

	free(game->ply);
	free_map(game->map);
	free(game->rays);
	free(game->z_buffer);
	free(game->fps);
	free_languages(game);
	if (game->serverThread)
	{
		pthread_cancel(game->serverThread);
		pthread_join(game->serverThread, NULL);
		close(game->serverStatus.serverSocket);
	}

	free_window(game->window);
	exit_editor(game);
	free_sounds(&game->sounds);
	free(game);
	TTF_Quit();
	SDL_Quit();
	ft_printf("And fish for all the thanks!\n");
	exit(0);
}
