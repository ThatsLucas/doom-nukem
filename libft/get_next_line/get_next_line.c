/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:51:13 by aabouyaz          #+#    #+#             */
/*   Updated: 2025/09/07 09:58:50 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_result(char *s)
{
	int		i;
	char	*res;
	int		len;

	len = bn_pos(s);
	if (len == 0)
		len = (int)ft_strlen(s);
	if (!s)
		return (NULL);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s && i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	if (res[0] == 0)
	{
		free(res);
		res = NULL;
	}
	return (res);
}

static char	*free_all_cases(char ***res)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		if ((*res) && (*res)[i])
		{
			free((*res)[i]);
			(*res)[i] = NULL;
		}
		i++;
	}
	free(*res);
	*res = NULL;
	return (NULL);
}

void	freeall_gnl(char ***res, int fd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (fd > 1023 || fd < 0)
		return ;
	free((*res)[fd]);
	(*res)[fd] = NULL;
	while (i < 1024)
	{
		if ((*res)[i] != NULL)
			j++;
		i++;
	}
	if (j == 0)
	{
		free(*res);
		*res = NULL;
	}
}

void	alloc_remain(char ***rem)
{
	int	i;

	i = 0;
	if (!*rem)
	{
		*rem = malloc(sizeof(char *) * 1024);
		if (!*rem)
			return ;
		while (i < 1024)
		{
			(*rem)[i] = NULL;
			i++;
		}
	}
}

char	*get_next_line(int fd)
{
	int			r;
	static char	**remain = NULL;
	char		*res;

	if (fd == -1)
		return (free_all_cases(&remain));
	alloc_remain(&remain);
	my_read(fd, &remain, &r);
	if (fd < 0 || r == -1 || fd > 1023)
	{
		freeall_gnl(&remain, fd);
		return (NULL);
	}
	while (r == BUFFER_SIZE && bn_pos(remain[fd]) == 0)
		my_read(fd, &remain, &r);
	if (bn_pos(remain[fd]) == 0)
	{
		res = get_result(remain[fd]);
		freeall_gnl(&remain, fd);
		return (res);
	}
	res = get_result(remain[fd]);
	new_remaining(&remain, fd);
	return (res);
}
