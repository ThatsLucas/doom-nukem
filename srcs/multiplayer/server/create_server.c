/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:30:24 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/26 16:19:53 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/server.h"
#include "multiplayer/shared.h"
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

void *create_server(void *gameStruct)
{
    t_game *game = (t_game *)gameStruct;
    int listenfd;
    unsigned int len;
    struct sockaddr_in servaddr, cliaddr;

    if (!game)
        return (NULL);

    bzero(&servaddr, sizeof(servaddr));

    // Create a UDP Socket
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    ft_printf("Created server on port : %d\n", PORT);
    t_client_udp_datas datas;
    while (1)
    {
        len = sizeof(cliaddr);
        bzero(&cliaddr, sizeof(cliaddr));
        int n = recvfrom(listenfd, &datas, sizeof(t_client_udp_datas),
                         0, (struct sockaddr *)&cliaddr, &len);
        if (n == -1)
            continue;
        create_notif(&game->window->menus.notif.notif_buf, "A new player joined the game!", 5, 80);
        char *IPV4 = ft_inet_ntoa(cliaddr.sin_addr);
        if (IPV4)
            ft_printf("A new player has joined the game with ip : %s\n", IPV4);
        free(IPV4);
        ft_bzero(&datas, sizeof(t_client_udp_datas));
    }
}
