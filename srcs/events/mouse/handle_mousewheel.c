/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mousewheel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:21:31 by edurance          #+#    #+#             */
/*   Updated: 2026/04/09 12:41:45 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	handle_mousewheel(t_game *game, SDL_MouseWheelEvent *wheel)
{
	t_inventory *inv = &game->ply->inventory;
	int			*weap_index = &game->ply->current_weap_index;
	int			scroll;

	if (inv->weap_count < 2)
		return ;

	scroll = wheel->y;
	if (wheel->direction == SDL_MOUSEWHEEL_FLIPPED)
		scroll *= -1;

	if (scroll > 0)
		*weap_index = (*weap_index + 1) % inv->weap_count;
	else
		*weap_index = (*weap_index - 1) % inv->weap_count;

	if (*weap_index < 0)
		*weap_index = inv->weap_count - 1;
}
