/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:16:04 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/20 13:54:51 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_SERVER_H
# define MULTI_SERVER_H

# include "../../libft/include/libft.h"
# include "multiplayer/shared.h"
# include <SDL.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <pthread.h>
# include <stdio.h>
# include <strings.h>
# include <sys/socket.h>
# include <sys/types.h>

void					*create_server(void *gameStruct);

typedef struct s_game	t_game;

typedef struct s_udp_server_status
{
	int					currentState;
	int					currentLevel;
	int					serverSocket;
	int					playerCount;
	struct sockaddr		address[4];
	Uint64				last_update[4];
	double				players[4][3]; // x, y, z des pieds
	double				player_angles[4];
	int					player_hp[4];

	// partage avec le thread principal de l'hote : proteger par lock
	pthread_mutex_t		lock;
	int					damage_total[4];						// degats cumules recus par chaque joueur
	int					hits_epoch[4];							// epoque des compteurs hits_seen
	int					hits_seen[4][MAX_NET_ENTITIES];			// derniers degats cumules recus de chaque joueur
	int					pending_damage[MAX_NET_ENTITIES];		// degats a appliquer par le thread principal
	int					entity_count;
	t_net_entity		entities[MAX_NET_ENTITIES];				// snapshot ecrit par le thread principal
}						t_udp_server_status;

void					send_to_client(t_server_udp_datas *datas, struct sockaddr *addr, int socket, int playerIndex);
void					send_default_info_response(t_game *game);
void					broadcast_message(t_game *game, int except, t_server_udp_datas *datas);
void					send_notifications(t_game *game, struct sockaddr *addr, char *str, int duration, int fontsize, int playerIndex);
void					broadcast_notifications(t_game *game, int except, char *str, int duration, int fontsize);
int						is_player_connected(t_game *game, struct sockaddr *client);
int						add_new_player(t_game *game, struct sockaddr *newClient);
void					remove_player(t_game *game, struct sockaddr *disconnectedPlayer);
void					handle_player_timeout(t_game *game);
void					fill_game_state(t_server_udp_datas *response, t_game *game);
void					apply_player_hits(t_game *game, t_client_udp_datas *datas, int playerIndex);
void					sync_host_entities(t_game *game);
void					damage_remote_player(t_game *game, int playerIndex, int damage);

#endif
