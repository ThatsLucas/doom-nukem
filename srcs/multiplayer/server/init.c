/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root- <root-@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:15:11 by root-             #+#    #+#             */
/*   Updated: 2026/06/22 11:28:39 by root-            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/multiplayer.h"

void *start_server_thread(void *serverStruct)
{
    int socketFD;
    struct sockaddr_in addr;
    (void)serverStruct;

    if ((socketFD = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET; // IPv4
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(MULTIPLAYER_PORT);

    if (bind(socketFD, (const struct sockaddr *)&addr,
             sizeof(addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    ft_printf("Starting server\n");
    return (NULL);
}
