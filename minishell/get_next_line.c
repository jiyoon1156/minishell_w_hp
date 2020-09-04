/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 19:26:09 by jhur              #+#    #+#             */
/*   Updated: 2020/06/02 13:52:29 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	has_newline(char *buf, char *tmp, char **line)
{
	int i;

	if (ft_strchr(buf, '\n'))
	{
		i = -1;
		while (buf[++i] != '\n')
			tmp[i] = buf[i];
		tmp[i] = '\0';
		if (!(*line = ft_strjoin_gnl(*line, tmp)))
			return (-1);
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	size_t		res;
	char		buf[BUFFER_SIZE + 1];
	char		tmp[BUFFER_SIZE + 1];

	if (fd < 0 || line == NULL || (read(fd, buf, 0) < 0) || BUFFER_SIZE < 1)
		return (-1);
	*line = ft_strdup("");
	while (*line != '\0')
	{
		while ((res = read(fd, buf, BUFFER_SIZE)) > 0)
		{
			buf[res] = '\0';
			if (has_newline(buf, tmp, line) == 1)
				return (1);
			if (!(*line = ft_strjoin_gnl(*line, buf)))
				return (-1);
		}
		if (res == 0 && ft_strlen(*line) == 0)
			return (0);
	}
	return (res);
}
