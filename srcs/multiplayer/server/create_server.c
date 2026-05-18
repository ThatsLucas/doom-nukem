/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:30:24 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/18 14:22:58 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/server.h"
#include "multiplayer/shared.h"

void create_server(void)
{
    int listenfd;
    unsigned int len;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));

    // Create a UDP Socket
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    char buffer[100];
    while (1)
    {
        int n = recvfrom(listenfd, buffer, sizeof(buffer),
                         0, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        ft_printf("Received : %s\n", buffer);
    }
}