/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:59:56 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/26 14:51:08 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplayer/client.h"

int get_server_response(t_udp_connections *connection, t_server_udp_datas *datas)
{
    ssize_t n = recvfrom(connection->con_socket, &datas, sizeof(t_server_udp_datas), 0, NULL, NULL);
    if (n > 0 && n == sizeof(t_server_udp_datas))
    {
        // TODO checksum pour check si data corrompu ?
        return (1);
    }
    return (0);
}