/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_sync.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:00:00 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/28 12:00:00 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/client.h"
#include "Game.h"

/* Client : applique l’état des entités envoyé par l’hôte. */
void apply_server_entities(t_server_udp_datas *datas, t_game *game)
{
    t_entity *e;
    t_net_entity *net;

    // l'hote simule lui-meme ses entites
    if (game->settings.is_host || datas->state != 2 || !game->map)
        return;
    if (datas->level != game->current_level || datas->entity_count <= 0)
        return;
    // meme map = memes entites dans le meme ordre, sinon on ne touche a rien
    if (datas->entity_count != game->entities.count
        && !(game->entities.count > MAX_NET_ENTITIES && datas->entity_count == MAX_NET_ENTITIES))
        return;
    for (int i = 0; i < datas->entity_count; i++)
    {
        e = &game->entities.list[i];
        net = &datas->entities[i];
        if (net->sector < 0 || net->sector >= game->map->num_sectors)
            continue;
        e->x = net->x;
        e->y = net->y;
        e->dir_x = net->dir_x;
        e->dir_y = net->dir_y;
        e->hp = net->hp;
        e->sector = net->sector;
        e->status = (t_entity_status)net->status;
        if (e->status == E_STATUS_DEAD)
            e->hitbox = 0;
    }
}

/* Client : retient les dégâts infligés à une entité, l’hôte les appliquera. */
void report_entity_hit(t_game *game, int entityIndex, int damage)
{
    if (entityIndex < 0 || entityIndex >= MAX_NET_ENTITIES || damage <= 0)
        return;
    game->clientConnection.dealt[entityIndex] += damage;
}
