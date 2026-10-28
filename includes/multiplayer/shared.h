/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:16:04 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/20 13:55:44 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_SHARED_H
# define MULTI_SHARED_H

// #include "Player.h"

# define PORT 2026
# define TIMEOUT_DURATION 2000			// time before we considere player disconnected or crash or whatever happened
# define LOADING_GRACE_DURATION 15000	// extra time given to clients to load the map when the game starts
# define MAX_NET_ENTITIES 128			// entites synchronisees (meme ordre partout : spawn depuis la map)

/* etat d'une entite envoye par le serveur (l'hote fait autorite) */
typedef struct s_net_entity
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	int		hp;
	int		status;
	int		sector;
}			t_net_entity;

typedef struct s_client_udp_datas
{
	int		state;	// joining will be 1, 2 is in lobby, 3 is in game, 4 is leaving
	int		level;	// if state 2 else 0
	float	x;
	float	y;
	float	z;		// hauteur des pieds (jetpack, saut)
	float	ang;
	int		hp;

	int		hits_epoch;	// incremente a chaque chargement de niveau
	// degats cumules infliges a chaque entite du niveau courant
	// (cumules pour qu'un paquet perdu ne perde pas de degats)
	int		dealt[MAX_NET_ENTITIES];

}			t_client_udp_datas;

typedef struct s_server_udp_datas
{
	int		state;			// 1 lobby, 2 ingame, 3 game stop, 4 game full
	int		level;			// if state 2 else 0
	int		playerCount;
	double	players[4][3];	// x, y, z des pieds
	float	player_angles[4];
	int		player_hp[4];
	int		playerIndex;
	int		damage_total;	// degats cumules recus par le destinataire

	int				entity_count;
	t_net_entity	entities[MAX_NET_ENTITIES];

	// notifications handling
	int		is_notif;		// bool
	int		notif_duration;
	int		notif_font_size;
	char	notif_str[256];
}			t_server_udp_datas;

#endif
