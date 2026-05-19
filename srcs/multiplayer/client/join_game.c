/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:46:06 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/19 11:29:03 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/client.h"
#include "multiplayer/shared.h"

void send_join_request(char *serveraddr)
{
    int sockfd;
    struct sockaddr_in servaddr;

    // clear servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr(serveraddr);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    sendto(sockfd, "join_request", 5, MSG_CONFIRM, (struct sockaddr *)&servaddr, sizeof(servaddr));
}

int main(void)
{
    send_join_request("127.0.0.1");
}