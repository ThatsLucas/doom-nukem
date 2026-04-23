/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 12:17:22 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/17 11:16:16 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.h"
#include "GUI/GUI.h"
#include "Game.h"

static void mouse_x(int x, t_ply *pl)
{
	t_vect2 old_dir;
	float angle;

	if (abs(x) < 3)
		return;
	angle = 0.0005f * x;

	old_dir = pl->dir;

	pl->dir.x = old_dir.x * cosf(angle) - old_dir.y * sinf(angle);

	pl->dir.y = old_dir.x * sinf(angle) + old_dir.y * cosf(angle);
}

static void mouse_y(int y, t_ply *pl, t_game *game)
{
	int newpitch;

	newpitch = pl->pitch;
	newpitch += -y;

	if (newpitch <= game->screenSize[1] && newpitch > -(game->screenSize[1]))
		pl->pitch = newpitch;
}

/*hook pour les mouvements de souris (directions)*/
void mouse_moves(int x, int y, t_game *game)
{
	static int middle_x = 0;
	static int middle_y = 0;

	if (!x && !y)
		return;
	if (game->window->menus.current != 0)
		return;
	if (!middle_x)
	{
		middle_x = game->screenSize[0] / 2;
		middle_y = game->screenSize[1] / 2;
	}
	mouse_x(x, game->ply);
	mouse_y(y, game->ply, game);

	SDL_WarpMouseInWindow(game->window->winPTR, middle_x, middle_y);
	return;
}