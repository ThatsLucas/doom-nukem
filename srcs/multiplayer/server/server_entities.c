/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:00:00 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/28 12:00:00 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/server.h"
#include "Game.h"

/* Ajoute aux dégâts en attente ce que le joueur a infligé depuis son dernier paquet.
   Appelé par le thread serveur, lock déjà pris. */
void apply_player_hits(t_game *game, t_client_udp_datas *datas, int playerIndex)
{
    t_udp_server_status *s = &game->serverStatus;

    // paquet d'avant le dernier chargement de niveau : compteurs perimes
    if (datas->hits_epoch < s->hits_epoch[playerIndex])
        return;
    // niveau recharge : le client a remis ses compteurs a zero
    if (datas->hits_epoch > s->hits_epoch[playerIndex])
    {
        ft_bzero(s->hits_seen[playerIndex], sizeof(s->hits_seen[playerIndex]));
        s->hits_epoch[playerIndex] = datas->hits_epoch;
    }
    for (int i = 0; i < MAX_NET_ENTITIES; i++)
    {
        // compteurs cumules : un paquet perdu ou en retard ne fausse rien
        if (datas->dealt[i] > s->hits_seen[playerIndex][i])
        {
            s->pending_damage[i] += datas->dealt[i] - s->hits_seen[playerIndex][i];
            s->hits_seen[playerIndex][i] = datas->dealt[i];
        }
    }
}

/* Applique à une entité les dégâts d’un joueur distant. */
static void damage_entity(t_entity *e, int damage)
{
    if (damage <= 0 || e->status == E_STATUS_DEAD)
        return;
    e->hp -= damage;
    if (e->hp <= 0)
    {
        e->status = E_STATUS_DEAD;
        e->hitbox = 0;
    }
}

/* Copie l’état d’une entité dans le format réseau. */
static void entity_to_net(t_entity *e, t_net_entity *net)
{
    net->x = e->x;
    net->y = e->y;
    net->dir_x = e->dir_x;
    net->dir_y = e->dir_y;
    net->hp = e->hp;
    net->status = e->status;
    net->sector = e->sector;
}

/* Hôte : applique les dégâts des autres joueurs et publie l’état des entités. */
void sync_host_entities(t_game *game)
{
    t_udp_server_status *s = &game->serverStatus;
    int count = game->entities.count;

    if (count > MAX_NET_ENTITIES)
        count = MAX_NET_ENTITIES;
    pthread_mutex_lock(&s->lock);
    if (s->currentState != 2 || game->current_level != s->currentLevel || !game->map)
    {
        ft_bzero(s->pending_damage, sizeof(s->pending_damage));
        s->entity_count = 0;
        pthread_mutex_unlock(&s->lock);
        return;
    }
    for (int i = 0; i < count; i++)
    {
        damage_entity(&game->entities.list[i], s->pending_damage[i]);
        entity_to_net(&game->entities.list[i], &s->entities[i]);
    }
    ft_bzero(s->pending_damage, sizeof(s->pending_damage));
    s->entity_count = count;
    pthread_mutex_unlock(&s->lock);
}

/* Hôte : une entité touche un joueur distant, il le saura au prochain paquet. */
void damage_remote_player(t_game *game, int playerIndex, int damage)
{
    if (damage <= 0 || playerIndex < 0 || playerIndex >= 4)
        return;
    pthread_mutex_lock(&game->serverStatus.lock);
    game->serverStatus.damage_total[playerIndex] += damage;
    pthread_mutex_unlock(&game->serverStatus.lock);
}
