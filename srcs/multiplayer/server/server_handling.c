/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:30:24 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/27 16:33:53 by lle-duc          ###   ########.fr       */
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
        ft_bzero(&datas, sizeof(t_client_udp_datas));
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
