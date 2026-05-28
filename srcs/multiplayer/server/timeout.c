/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeout.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:15:51 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/28 11:44:24 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/server.h"
#include "Game.h"

void handle_player_timeout(t_game *game)
{
    Uint64 curTime = SDL_GetTicks64();
    int playerCount = game->serverStatus.playerCount;
    for (int i = 0; i < playerCount; i++)
    {
        if (game->serverStatus.last_update[i] + TIMEOUT_DURATION < curTime) // player do not responded in time
        {
            remove_player(game, &game->serverStatus.address[i]);
            ft_printf("Player #%d has timed out\n", i);
        }
    }
}