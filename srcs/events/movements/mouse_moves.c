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

static void	mouse_x(int x, int middle_x, t_ply *pl)
{
	t_vect2		old_dir;
	float		angle;

	angle = 0.03f;
	old_dir.x = pl->dir.x;
	if (x + 10 < middle_x)
	{
		pl->dir.x = old_dir.x * cosf(angle * -1) - pl->dir.y * sinf(angle * -1);
		pl->dir.y = old_dir.x * sinf(angle * -1) + pl->dir.y * cosf(angle * -1);
	}
	if (x > middle_x + 10)
	{
		pl->dir.x = old_dir.x * cosf(angle) - pl->dir.y * sinf(angle);
		pl->dir.y = old_dir.x * sinf(angle) + pl->dir.y * cosf(angle);
	}
}

static void	mouse_y(int y, int middle_y, t_ply *pl, t_game *game)
{
	int	oldpitch;
	int	step;

	oldpitch = pl->pitch;
	step = 15;
	if (y + 10 < middle_y)
		pl->pitch += step;
	if (y > middle_y + 10)
		pl->pitch -= step;

	if (pl->pitch > game->screenSize[1] || pl->pitch <= -(game->screenSize[1]))
		pl->pitch = oldpitch;
	return ;
}

/*hook pour les mouvements de souris (directions)*/
void	mouse_moves(int x, int y, t_game *game)
{
	static int	middle_x = 0;
	static int	middle_y = 0;

	if (game->status <= 0)
		return ;
	if (!middle_x)
	{
		middle_x = game->screenSize[0] / 2;
		middle_y = game->screenSize[1] / 2;
	}
	mouse_x(x, middle_x, game->ply);
	mouse_y(y, middle_y, game->ply, game);

	SDL_WarpMouseInWindow(game->window->winPTR, middle_x, middle_y);
	return ;
}

