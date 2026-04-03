/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:57:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2025/09/04 17:11:36 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	bn_pos(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

// concatene buff dans *s qui est un malloc
void	mconcat(char ***s, char *buf, int fd)
{
	char	*snew;
	int		i;
	int		j;

	snew = malloc((ft_strlen((*s)[fd]) + ft_strlen(buf) + 1) * sizeof(char));
	if (!snew)
		return ;
	i = 0;
	while ((*s)[fd] && (*s)[fd][i])
	{
		snew[i] = (*s)[fd][i];
		i++;
	}
	j = 0;
	while (buf[j])
	{
		snew[i + j] = buf[j];
		j++;
	}
	snew[i + j] = 0;
	if ((*s)[fd])
		free((*s)[fd]);
	(*s)[fd] = snew;
}

// mon read qui mets a jour directement mon rem et mon res ici.
void	my_read(int fd, char ***rem, int *res)
{
	char	*buffer;

	if (fd < 0)
		return ;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return ;
	*res = read(fd, buffer, BUFFER_SIZE);
	if (*res <= 0)
	{
		free(buffer);
		buffer = NULL;
		return ;
	}
	buffer[*res] = 0;
	mconcat(rem, buffer, fd);
	free(buffer);
	buffer = NULL;
}

//	mets a jour remaining apres le \n ou tout le reste si il y en a aucun
void	new_remaining(char ***rem, int fd)
{
	char	*newrem;
	int		i;
	int		bn;

	bn = bn_pos((*rem)[fd]);
	newrem = malloc((ft_strlen((*rem)[fd]) - bn + 1) * sizeof(char));
	if (!newrem)
	{
		free((*rem)[fd]);
		(*rem)[fd] = NULL;
		return ;
	}
	i = -1;
	while (*rem && (*rem)[fd][++i + bn])
		newrem[i] = (*rem)[fd][i + bn];
	newrem[i] = 0;
	free((*rem)[fd]);
	if (newrem[0] == 0)
	{
		free(newrem);
		newrem = NULL;
	}
	(*rem)[fd] = newrem;
}
