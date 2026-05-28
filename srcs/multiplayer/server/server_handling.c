/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:30:24 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/28 15:34:40 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/server.h"
#include "Game.h"

static char *ft_inet_ntoa(struct in_addr in)
{
    unsigned char *bytes = (unsigned char *)&in;

    char *str = malloc(sizeof(char) * (12 + 3 + 1)); // 3 numbers * 4 + 3 dots + \0
    if (!str)
        return (NULL);

    int j = -1;
    for (int i = 0; i < 4; i++)
    {
        char *nbrs = ft_itoa(bytes[i]);
        int len = ft_strlen(nbrs);
        for (int k = 0; k < len; k++)
        {
            str[++j] = nbrs[k];
        }
        if (i != 3)
            str[++j] = '.';
        free(nbrs);
    }
    str[++j] = '\0';

    return (str);
}

void send_to_client(t_server_udp_datas *datas, struct sockaddr *addr, int socket)
{
    sendto(socket, datas, sizeof(t_server_udp_datas), MSG_CONFIRM, addr, sizeof(struct sockaddr));
}

/*fonction pour traiter les demandes d'un joueur deja connecte*/
void handle_connected_player_request(t_game *game, t_client_udp_datas datas, struct sockaddr_in *player, int playerIndex)
{
    ft_printf("player request state %d\n", datas.state);

    if (datas.state == 3)
    {
        if (game->serverStatus.currentState == 2) // en jeu sinon on est en lobby
        {
            game->serverStatus.players[playerIndex][0] = datas.x;
            game->serverStatus.players[playerIndex][1] = datas.y;
            ft_printf("Player pos updated\n");
        }
        else
        {
            char *IPV4 = ft_inet_ntoa(player->sin_addr);
            if (ft_strcmp(IPV4, "127.0.0.1") == 0)
            {
                game->serverStatus.currentState = 2;
                game->serverStatus.currentState = datas.level;
                if (datas.level < 1 || datas.level > 3)
                    game->serverStatus.currentState = 1;
                ft_printf("Host asked to start the game, starting...\n");
            }
            free(IPV4);
        }
    }
    if (datas.state == 4)
    {
        remove_player(game, (struct sockaddr *)player);
        broadcast_notifications(game, playerIndex, "A player has left the game", 5, 50);
        return;
    }

    game->serverStatus.last_update[playerIndex] = SDL_GetTicks64();
}

/*Loop infini pour recevoir les msg*/
void receive_connections(int listenfd, t_game *game)
{
    unsigned int len;
    t_client_udp_datas datas;
    struct sockaddr_in cliaddr;

    while (1)
    {
        len = sizeof(cliaddr);
        bzero(&cliaddr, sizeof(struct sockaddr_in));
        int n = recvfrom(listenfd, &datas, sizeof(t_client_udp_datas),
                         0, (struct sockaddr *)&cliaddr, &len);
        if (n == -1)
            continue;
        int playerIndex = is_player_connected(game, (struct sockaddr *)&cliaddr);
        if (playerIndex == -1)
        {
            playerIndex = add_new_player(game, (struct sockaddr *)&cliaddr);
            if (playerIndex < 0)
                continue;
            broadcast_notifications(game, playerIndex, "A new player has joined the game", 5, 50);
            char *IPV4 = ft_inet_ntoa(cliaddr.sin_addr);
            if (IPV4)
                ft_printf("A new player has joined the game with ip : %s\n", IPV4);
            free(IPV4);
        }
        else
            handle_connected_player_request(game, datas, &cliaddr, playerIndex);
        ft_bzero(&datas, sizeof(t_client_udp_datas));
        send_default_info_response(game);
        handle_player_timeout(game);
    }
}

void *create_server(void *gameStruct)
{
    t_game *game = (t_game *)gameStruct;
    int listenfd;
    struct sockaddr_in servaddr;

    if (!game)
        return (NULL);

    bzero(&servaddr, sizeof(servaddr));

    // Create a UDP Socket
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;
    game->serverStatus.serverSocket = listenfd;

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    ft_printf("Created server on port : %d\n", PORT);

    receive_connections(listenfd, game);

    return (NULL);
}
