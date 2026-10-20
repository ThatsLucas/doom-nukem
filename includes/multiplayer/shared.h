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

typedef struct s_client_udp_datas
{
	int		state;	// joining will be 1, 2 is in lobby, 3 is in game, 4 is leaving
	int		level;	// if state 2 else 0
	float	x;
	float	y;
	float	z;		// hauteur des pieds (jetpack, saut)
	float	ang;

	// t_ply players[10];

}			t_client_udp_datas;

typedef struct s_server_udp_datas
{
	int		state;			// 1 lobby, 2 ingame, 3 game stop, 4 game full
	int		level;			// if state 2 else 0
	int		playerCount;
	double	players[4][3];	// x, y, z des pieds
	float	player_angles[4];
	int		playerIndex;

	// notifications handling
	int		is_notif;		// bool
	int		notif_duration;
	int		notif_font_size;
	char	notif_str[256];
}			t_server_udp_datas;

#endif
